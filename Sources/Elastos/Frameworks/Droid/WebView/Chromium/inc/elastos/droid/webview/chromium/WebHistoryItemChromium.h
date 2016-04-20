
#ifndef _ELASTOS_DROID_WEBKIT_WEBVIEW_CHROMIUM_WEBHISTORYITEMCHROMIUM_H_
#define _ELASTOS_DROID_WEBKIT_WEBVIEW_CHROMIUM_WEBHISTORYITEMCHROMIUM_H_

#include "Elastos.Droid.Webkit.h"
#include "elastos/droid/ext/frameworkext.h"
#include "elastos/droid/webkit/webview/chromium/native/content/browser/NavigationEntry.h"

using Elastos::Droid::Graphics::IBitmap;
using Elastos::Droid::Webkit::Webview::Chromium::Content::Browser::NavigationEntry;
using Elastos::Droid::Webkit::IWebHistoryItem;

namespace Elastos {
namespace Droid {
namespace Webkit {
namespace Webview {
namespace Chromium {

/**
  * WebView Chromium implementation of WebHistoryItem. Simple immutable wrapper
  * around NavigationEntry
  */
class WebHistoryItemChromium
    : public Object
    , public IWebHistoryItem
{
public:
    CAR_INTERFACE_DECL()

    /* package */
    WebHistoryItemChromium(
        /* [in] */ NavigationEntry* entry);

    /**
      * See {@link android.webkit.WebHistoryItem#getId}.
      */
    // @Override
    CARAPI GetId(
        /* [out] */ Int32* id);

    /**
      * See {@link android.webkit.WebHistoryItem#getUrl}.
      */
    // @Override
    CARAPI GetUrl(
        /* [out] */ String* url);

    /**
      * See {@link android.webkit.WebHistoryItem#getOriginalUrl}.
      */
    // @Override
    CARAPI GetOriginalUrl(
        /* [out] */ String* url);

    /**
      * See {@link android.webkit.WebHistoryItem#getTitle}.
      */
    // @Override
    CARAPI GetTitle(
        /* [out] */ String* title);

    /**
      * See {@link android.webkit.WebHistoryItem#getFavicon}.
      */
    // @Override
    CARAPI GetFavicon(
        /* [out] */ IBitmap** bitMap);

    /**
      * See {@link android.webkit.WebHistoryItem#clone}.
      */
    // @Override
    // synchronized
    CARAPI Clone(
        /* [out] */ WebHistoryItemChromium** chromium);

private:
    // Clone constructor.
    WebHistoryItemChromium(
        /* [in] */ const String& url,
        /* [in] */ const String& originalUrl,
        /* [in] */ const String& title,
        /* [in] */ IBitmap* favicon);

private:
    const String mUrl;
    const String mOriginalUrl;
    const String mTitle;
    const AutoPtr<IBitmap> mFavicon;
};

} // namespace Chromium
} // namespace Webview
} // namespace Webkit
} // namespace Droid
} // namespace Elastos

#endif // _ELASTOS_DROID_WEBKIT_WEBVIEW_CHROMIUM_WEBHISTORYITEMCHROMIUM_H_
