#include "OrbitPrediction.h"

#include <chrono>
#include <iostream>



OrbitPoint::OrbitPoint(double pos_x, double pos_y, double vel_x, double vel_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    
    this->vel_x = vel_x;
    this->vel_y = vel_y;
}



double OrbitPoint::Speed() {
    return sqrt(pow(vel_x, 2) + pow(vel_y, 2));
}

double OrbitPoint::Distance(double parent_x, double parent_y) {
    return sqrt(pow(pos_x - parent_x, 2) + pow(pos_y - parent_y, 2));
}

double OrbitPoint::Angle(double parent_x, double parent_y) {
    return atan(pow(pos_x - parent_x, 2) / pow(pos_y - parent_y, 2));
}



vector<vector<OrbitPoint>> PredictOrbits(int total_time_step, int time_step_size, vector<Body> system) {

    int current_time_step = 0;
    vector<vector<OrbitPoint>> orbit_points;

    for (int i = 0; i < system.size(); i++) orbit_points.push_back(vector<OrbitPoint>());

    auto start = std::chrono::high_resolution_clock::now();
    while (current_time_step < total_time_step) {
        /* https://medium.com/python-in-plain-english/molecular-dynamics-velocity-verlet-integration-with-python-5ae66b63a8fd */

        // 0] Append current body information to orbit point vector
        for (int i = 0; i < system.size(); i++) {
            orbit_points[i].push_back(OrbitPoint(system[i].pos_x, system[i].pos_y, system[i].vel_x, system[i].vel_y));
        }

        // 1] Update velocities
        for (Body &body_to : system) {
            for (Body &body_from : system) {
                if (&body_to != &body_from) {
                    body_to.ApplyGravitationalForce(time_step_size, body_from);
                }
            }
        }

        // 2] Update positions;
        for (Body &body : system) {
            body.ApplyVelocity(time_step_size);
        }

        // 3] Move time forward
        current_time_step += 1;
    }
    
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Gravity simulation: " << (finish - start).count() << "\n";

    return orbit_points;
}