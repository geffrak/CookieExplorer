#include <QApplication>
#include <QtWebEngine/QtWebEngine>
#include <QtWidgets>
#include <QWebEngineView>
#include <QWebEngineProfile>

int main(int argc, char *argv[])
{
    // Basic stuffs
    QApplication app(argc, argv);
    QWebEngineView view;
    QNetworkCookieJar cookieJar;

    // Get the cookie store reference from the defaultProfile
    auto * profile = QWebEngineProfile::defaultProfile();
    auto * store = profile->cookieStore();  /** NOT EXPOSED TO PYSIDE2 **/

    // Forge a cookie
    QNetworkCookie cookie;
    cookie.setDomain(argv[1]);
    cookie.setName("My special cookie");
    cookie.setValue("SessionId -> !@#!@#!@#!@#!#");

    // Connect to the store to be able to keep the cookies
    QObject::connect(store, &QWebEngineCookieStore::cookieAdded, [&](const QNetworkCookie &cookie) { /** NOT EXPOSED TO PYSIDE2 **/
        cookieJar.insertCookie(cookie);
    });

    // Set my newly forged cookie
    store->setCookie(cookie, QUrl(argv[1])); /** NOT EXPOSED TO PYSIDE2 **/

    // Show my page
    view.setUrl(QUrl(argv[1]));
    view.show();
    app.exec();

    // Get every cookie related to my page.
    for (auto cookie : cookieJar.cookiesForUrl(QUrl(argv[1]))){
        qInfo() << "Domain:\t" << cookie.domain() << "\n"
                << "Name:\t"   << cookie.name() << "\n"
                << "Value:\t"  << cookie.value() << "\n"
                << "Due:\t" << cookie.expirationDate() << "\n";
    }

    return 0;
}