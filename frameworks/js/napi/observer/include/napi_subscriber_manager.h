/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NAPI_RDB_SUBSCRIBER_MANAGER_H
#define NAPI_RDB_SUBSCRIBER_MANAGER_H

#include <memory>
#include <uv.h>

#include "callbacks_manager.h"
#include "datashare_helper.h"
#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"
#include "napi_observer.h"

namespace OHOS {
namespace DataShare {
class NapiRdbSubscriberManager : public CallbacksManager<RdbObserverMapKey, NapiRdbObserver>{
public:
    using Key = RdbObserverMapKey;
    using Observer = NapiRdbObserver;
    using BaseCallbacks = CallbacksManager<RdbObserverMapKey, NapiRdbObserver>;
    explicit NapiRdbSubscriberManager(std::weak_ptr<DataShareHelper> dataShareHelper)
        : dataShareHelper_(dataShareHelper){};
    std::vector<OperationResult> AddObservers(napi_env env, napi_value callback, const std::vector<std::string> &uris,
        const TemplateId &templateId);
    std::vector<OperationResult> DelObservers(napi_env env, napi_value callback, const std::vector<std::string> &uris,
        const TemplateId &templateId);
    void Emit(const RdbChangeNode &changeNode);
    void UnSubscribeAllObservers();

private:
    std::weak_ptr<DataShareHelper> dataShareHelper_;
};

class NapiPublishedSubscriberManager : public CallbacksManager<PublishedObserverMapKey, NapiPublishedObserver>{
public:
    using Key = PublishedObserverMapKey;
    using Observer = NapiPublishedObserver;
    using BaseCallbacks = CallbacksManager<PublishedObserverMapKey, NapiPublishedObserver>;
    explicit NapiPublishedSubscriberManager(std::weak_ptr<DataShareHelper> dataShareHelper)
        : dataShareHelper_(dataShareHelper){};
    std::vector<OperationResult> AddObservers(napi_env env, napi_value callback, const std::vector<std::string> &uris,
        int64_t subscriberId);
    std::vector<OperationResult> DelObservers(napi_env env, napi_value callback, const std::vector<std::string> &uris,
        int64_t subscriberId);
    void Emit(const PublishedDataChangeNode &changeNode);
    void UnSubscribeAllObservers();

private:
    std::weak_ptr<DataShareHelper> dataShareHelper_;
};
} // namespace DataShare
} // namespace OHOS
#endif //NAPI_RDB_SUBSCRIBER_MANAGER_H
