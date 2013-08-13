// Default empty project template
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

//use for calendar
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager.hpp>
#include <bb/system/InvokeReply.hpp>
#include <QDateTime>
#include <bb/PpsObject>
#include <bb/pim/calendar/CalendarEvent>

using namespace bb::cascades;
using namespace bb::system;
using namespace bb::pim::calendar;

ApplicationUI::ApplicationUI(bb::cascades::Application *app)
: QObject(app),
	m_invokeManager(new InvokeManager(this))
{
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
