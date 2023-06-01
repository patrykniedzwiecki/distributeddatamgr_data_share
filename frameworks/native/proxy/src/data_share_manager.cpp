/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "data_share_manager_impl.h"
#include "data_share_manager.h"
#include "uri.h"
#include "datashare_log.h"


namespace OHOS::DataShare {
std::shared_ptr<IDataShareService> DataShareManager::GetDataShareService()
{
    return DataShareManagerImpl::GetInstance().GetDataShareService();
}

} // namespace OHOS::DataShare