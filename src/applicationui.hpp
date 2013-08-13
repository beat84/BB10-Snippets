// Default empty project template
#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() {}

    Q_INVOKABLE void addToCal(QString date, QString subject);

private:
    bb::system::InvokeManager *m_invokeManager;
};


#endif /* ApplicationUI_HPP_ */
