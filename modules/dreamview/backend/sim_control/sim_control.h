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

/**
 * @file
 */

#ifndef MODULES_DREAMVIEW_BACKEND_SIM_CONTROL_SIM_CONTROL_H_
#define MODULES_DREAMVIEW_BACKEND_SIM_CONTROL_SIM_CONTROL_H_

#include <string>

#include "gtest/gtest_prod.h"
#include "modules/common/adapters/adapter_manager.h"
#include "modules/dreamview/backend/common/dreamview_gflags.h"
#include "modules/dreamview/backend/map/map_service.h"

/**
 * @namespace apollo::dreamview
 * @brief apollo::dreamview
 */
namespace apollo {
namespace dreamview {

/**
 * @class SimControl
 * @brief A module that simulates a 'perfect control' algorithm, which assumes
 * an ideal world where the car can be perfectly placed wherever the planning
 * asks it to be, with the expected speed, acceleration, etc.
 */
class SimControl {
 public:
  /**
 * @brief Constructor of SimControl.
 * @param map_service the pointer of MapService.
 */
  explicit SimControl(const MapService *map_service);

  /**
   * @brief Starts the timer to publish simulated localization and chassis
   * messages.
   */
  void Start();

  /**
   * @brief Stops the timer.
   */
  void Stop();

 private:
  void OnPlanning(const apollo::planning::ADCTrajectory &trajectory);
  void OnRoutingResponse(const apollo::routing::RoutingResponse &routing);

  // Reset the start point, which can be a dummy point on the map or received
  // from the routing module.
  void SetStartPoint(const double x, const double y);

  void Freeze();

  double AbsoluteTimeOfNextPoint();
  bool NextPointWithinRange();

  void TimerCallback(const ros::TimerEvent &event);

  void PublishChassis(double lambda);
  void PublishLocalization(double lambda);

  template <typename T>
  T Interpolate(T prev, T next, double lambda) {
    return (1 - lambda) * prev + lambda * next;
  }

  const MapService *map_service_;

  // The timer to publish simulated localization and chassis messages.
  ros::Timer sim_control_timer_;

  // Time interval of the timer, in seconds.
  static constexpr double kSimControlInterval = 0.01;

  // The latest received planning trajectory.
  apollo::planning::ADCTrajectory current_trajectory_;
  // The index of the previous and next point with regard to the
  // current_trajectory.
  int prev_point_index_;
  int next_point_index_;

  // Whether there's a planning received after the most recent routing.
  bool received_planning_;

  // Whether it is the first time the SimControl gets started.
  bool initial_start_;

  // Whether the sim control is enabled.
  bool enabled_;

  apollo::common::TrajectoryPoint prev_point_;
  apollo::common::TrajectoryPoint next_point_;

  FRIEND_TEST(SimControlTest, Test);
};

}  // namespace dreamview
}  // namespace apollo

#endif  // MODULES_DREAMVIEW_BACKEND_SIM_CONTROL_SIM_CONTROL_H_
