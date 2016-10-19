
#include "Elastos.Droid.App.h"
#include "Elastos.Droid.Net.h"
#include "elastos/droid/dialer/calllog/CCallLogNotificationsService.h"
#include "elastos/droid/dialer/calllog/DefaultVoicemailNotifier.h"
#include "elastos/utility/logging/Logger.h"

using Elastos::Droid::Content::IContentResolver;
using Elastos::Droid::Dialer::CallLog::EIID_ICallLogNotificationsService;
using Elastos::Droid::Net::IUri;
using Elastos::Utility::Logging::Logger;

namespace Elastos {
namespace Droid {
namespace Dialer {
namespace CallLog {

const String CCallLogNotificationsService::TAG("CallLogNotificationsService");

CAR_INTERFACE_IMPL(CCallLogNotificationsService, IntentService, ICallLogNotificationsService)

CAR_OBJECT_IMPL(CCallLogNotificationsService)

ECode CCallLogNotificationsService::constructor()
{
    return IntentService::constructor(TAG);
}

ECode CCallLogNotificationsService::OnCreate()
{
    IntentService::OnCreate();

    AutoPtr<IContentResolver> resolver;
    GetContentResolver((IContentResolver**)&resolver);
    mCallLogQueryHandler = new CallLogQueryHandler();
    mCallLogQueryHandler->constructor(resolver, NULL /*listener*/);
    return NOERROR;
}

ECode CCallLogNotificationsService::OnHandleIntent(
    /* [in] */ IIntent* intent)
{
    if (intent == NULL) {
        Logger::D(TAG, "onHandleIntent: could not handle null intent");
        return NOERROR;
    }

    String action;
    intent->GetAction(&action);
    if (ICallLogNotificationsService::ACTION_MARK_NEW_VOICEMAILS_AS_OLD.Equals(action)) {
        mCallLogQueryHandler->MarkNewVoicemailsAsOld();
    }
    else if (ICallLogNotificationsService::ACTION_UPDATE_NOTIFICATIONS.Equals(action)) {
        AutoPtr<IParcelable> parcelable;
        intent->GetParcelableExtra(
                ICallLogNotificationsService::EXTRA_NEW_VOICEMAIL_URI, (IParcelable**)&parcelable);
        AutoPtr<IUri> voicemailUri = IUri::Probe(parcelable);
        DefaultVoicemailNotifier::GetInstance(this)->UpdateNotification(voicemailUri);
    }
    else {
        Logger::D(TAG, "onHandleIntent: could not handle: %s", TO_CSTR(intent));
    }

    return NOERROR;
}

} // CallLog
} // Dialer
} // Droid
} // Elastos

