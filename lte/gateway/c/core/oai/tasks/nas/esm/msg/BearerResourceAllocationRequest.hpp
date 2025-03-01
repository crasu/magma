/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the terms found in the LICENSE file in the root of this source tree.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

#ifndef BEARER_RESOURCE_ALLOCATION_REQUEST_H_
#define BEARER_RESOURCE_ALLOCATION_REQUEST_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "lte/gateway/c/core/oai/tasks/nas/ies/MessageType.h"
#include "lte/gateway/c/core/oai/tasks/nas/ies/LinkedEpsBearerIdentity.h"
#include "lte/gateway/c/core/oai/tasks/nas/ies/TrafficFlowAggregateDescription.h"
#include "lte/gateway/c/core/oai/include/EpsQualityOfService.h"
#include "lte/gateway/c/core/oai/lib/3gpp/3gpp_23.003.h"
#include "lte/gateway/c/core/oai/lib/3gpp/3gpp_24.007.h"
#include "lte/gateway/c/core/oai/lib/3gpp/3gpp_24.008.h"
#ifdef __cplusplus
}
#endif

/* Minimum length macro. Formed by minimum length of each mandatory field */
#define BEARER_RESOURCE_ALLOCATION_REQUEST_MINIMUM_LENGTH \
  (TRAFFIC_FLOW_AGGREGATE_DESCRIPTION_MINIMUM_LENGTH +    \
   EPS_QUALITY_OF_SERVICE_MINIMUM_LENGTH)

/* Maximum length macro. Formed by maximum length of each field */
#define BEARER_RESOURCE_ALLOCATION_REQUEST_MAXIMUM_LENGTH \
  (TRAFFIC_FLOW_AGGREGATE_DESCRIPTION_MAXIMUM_LENGTH +    \
   EPS_QUALITY_OF_SERVICE_MAXIMUM_LENGTH +                \
   PROTOCOL_CONFIGURATION_OPTIONS_IE_MAX_LENGTH)

/* If an optional value is present and should be encoded, the corresponding
 * Bit mask should be set to 1.
 */
#define BEARER_RESOURCE_ALLOCATION_REQUEST_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT \
  (1 << 0)

typedef enum bearer_resource_allocation_request_iei_tag {
  BEARER_RESOURCE_ALLOCATION_REQUEST_PROTOCOL_CONFIGURATION_OPTIONS_IEI =
      SM_PROTOCOL_CONFIGURATION_OPTIONS_IEI,
} bearer_resource_allocation_request_iei;

/*
 * Message name: Bearer resource allocation request
 * Description: This message is sent by the UE to the network to request the
 * allocation of a dedicated bearer resource. See table 8.3.8.1. Significance:
 * dual Direction: UE to network
 */

typedef struct bearer_resource_allocation_request_msg_tag {
  /* Mandatory fields */
  eps_protocol_discriminator_t protocoldiscriminator : 4;
  ebi_t epsbeareridentity : 4;
  pti_t proceduretransactionidentity;
  message_type_t messagetype;
  linked_eps_bearer_identity_t linkedepsbeareridentity;
  traffic_flow_aggregate_description_t trafficflowaggregate;
  EpsQualityOfService requiredtrafficflowqos;
  /* Optional fields */
  uint32_t presencemask;
  protocol_configuration_options_t protocolconfigurationoptions;
} bearer_resource_allocation_request_msg;

int decode_bearer_resource_allocation_request(
    bearer_resource_allocation_request_msg* bearerresourceallocationrequest,
    uint8_t* buffer, uint32_t len);

int encode_bearer_resource_allocation_request(
    bearer_resource_allocation_request_msg* bearerresourceallocationrequest,
    uint8_t* buffer, uint32_t len);

#endif /* ! defined(BEARER_RESOURCE_ALLOCATION_REQUEST_H_) */
