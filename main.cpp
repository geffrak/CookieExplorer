#include <QApplication>
#include <QtWebEngine/QtWebEngine>
#include <QtWidgets>
#include <QWebEngineView>
#include <QWebEngineProfile>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QWebEngineProfile::defaultProfile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
    QWebEngineView view;

    auto * profile = QWebEngineProfile::defaultProfile();
    auto * store = profile->cookieStore();

    QObject::connect(store, &QWebEngineCookieStore::cookieAdded, [&](const QNetworkCookie &cookie) {
        qInfo() << "Domain:\t" << cookie.domain() << "\n"
                 << "Name:\t"   << cookie.name() << "\n"
                 << "Value:\t"  << cookie.value() << "\n"
                 << "Due:\t" << cookie.expirationDate() << "\n";
    });

    view.setUrl(QUrl(argv[1]));
    view.show();

    return app.exec();
}