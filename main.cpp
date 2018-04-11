#include <QApplication>
#include <QtWebEngine/QtWebEngine>
#include <QtWidgets>
#include <QWebEngineView>
#include <QWebEngineProfile>

int main(int argc, char *argv[])
{
    // Basic stuffs
    QApplication app(argc, argv);

    QQuickWebEngineProfile::defaultProfile()->setPersistentCookiesPolicy(QQuickWebEngineProfile::ForcePersistentCookies);

    // Get the cookie store reference from the defaultProfile
    auto * profile = QQuickWebEngineProfile::defaultProfile();
    auto * store = profile->cookieStore();
    //store->deleteAllCookies();

    // Connect to the store to be able to keep the cookies
    QObject::connect(store, &QWebEngineCookieStore::cookieAdded, [&](const QNetworkCookie &cookie) {
        qInfo() << "Domain:\t" << cookie.domain() << "\n"
                << "Name:\t"   << cookie.name() << "\n"
                << "Value:\t"  << cookie.value() << "\n";
    });


    QQmlApplicationEngine engine;

    QString url(argv[1]);
    engine.rootContext()->setContextProperty("link", url);

    engine.load(QUrl(QStringLiteral("../main.qml")));
    app.exec();

    return 0;
}