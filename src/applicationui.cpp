// Default empty project template
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

//used for calendar
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager.hpp>
#include <bb/system/InvokeReply.hpp>
#include <bb/PpsObject>

//used for Tracker
#include <QUuid>
#include <bb/device/DisplayInfo>

using namespace bb::cascades;
using namespace bb::system;

ApplicationUI::ApplicationUI(bb::cascades::Application *app)
: QObject(app),
	m_invokeManager(new InvokeManager(this))
{
	//add this line to be able to get Display information from QML
	qmlRegisterType<bb::device::DisplayInfo>("bb.display", 1, 0, "DisplayInfo");
	// create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_app", this);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}

void ApplicationUI::addToCal(QString date, QString subject){
	InvokeRequest cardRequest;

	cardRequest.setTarget("sys.pim.calendar.viewer.eventcreate");
	cardRequest.setAction("bb.action.EDIT");
	cardRequest.setMimeType("text/calendar");

	QDate clean_date = QDate::fromString(date, "yyyy-MM-dd");

	QTime new_time(14, 0, 0); //using a fixed hour - 2pm
	QDateTime date_time( clean_date, new_time );

	QVariantMap map;
	map.insert(QString("subject"), subject);
	map.insert(QString("startTime"), date_time.toString());
	map.insert(QString("duration"), 60); //using a fixed duration - 1h

	bool ok;
	QByteArray encData = bb::PpsObject::encode(map, &ok);
	cardRequest.setData(encData);
	cardRequest.setMetadata(map);
	InvokeTargetReply* reply = m_invokeManager->invoke(cardRequest);
}

QString ApplicationUI::trackerUUID(){
	QString trackerUUID = QUuid::createUuid();
	trackerUUID = trackerUUID.replace("{","");
	trackerUUID = trackerUUID.replace("}", "");

	qDebug() << "!!! UUID generated(): "+trackerUUID;
	return trackerUUID; //to keep the session, you have to store it into the app every time your app is installed. You have to reuse it instead of generate another one every time the app is launched.
}
