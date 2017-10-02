/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef MODULES_DRIVERS_DELPHI_ESR_PROTOCOL_ESR_TRACKMOTIONPOWER_540_H_
#define MODULES_DRIVERS_DELPHI_ESR_PROTOCOL_ESR_TRACKMOTIONPOWER_540_H_

#include "modules/drivers/proto/delphi_esr.pb.h"
#include "modules/drivers/sensor_protocol_data.h"

namespace apollo {
namespace drivers {
namespace delphi_esr {

using apollo::drivers::DelphiESR;

class Esrtrackmotionpower540 : public SensorProtocolData<DelphiESR> {
 public:
  static const int32_t ID;
  Esrtrackmotionpower540();
  void Parse(const std::uint8_t* bytes, int32_t length,
             DelphiESR* delphi_esr) const override;

 private:
  // config detail: {'name': 'CAN_TX_TRACK_ROLLING_COUNT_2', 'offset': 0.0,
  // 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range':
  // '[0|1]', 'bit': 4, 'type': 'bool', 'order': 'motorola', 'physical_unit':
  // ''}
  bool can_tx_track_rolling_count_2(const std::uint8_t* bytes,
                                    const int32_t length) const;
  int32_t can_tx_track_can_id_group(const std::uint8_t* bytes,
                                    int32_t length) const;
  bool can_tx_track_moving(const std::uint8_t* bytes, int32_t length,
                           int32_t index) const;
  bool can_tx_track_moving_fast(const std::uint8_t* bytes, int32_t length,
                                int32_t index) const;
  bool can_tx_track_moving_slow(const std::uint8_t* bytes, int32_t length,
                                int32_t index) const;
  int32_t can_tx_track_power(const std::uint8_t* bytes, int32_t length,
                             int32_t index) const;
};

}  // namespace delphi_esr
}  // namespace drivers
}  // namespace apollo

#endif  // MODULES_CANBUS_VEHICL_ESR_PROTOCOL_ESR_TRACKMOTIONPOWER_540_H_
