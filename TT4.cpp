#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "matplotlibcpp.h"

using namespace std;

namespace plt = matplotlibcpp;

// Gravity Constant
const double G = 6.67430e-11;  // (m^3 kg^-1 s^-2)

// Define Pi
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to solve Newton's Law equations and return the trajectory
std::vector<std::vector<double>> newtons_law(double m, double sm, double sma, double np) {
    // Variables for initial conditions
    double x = sma;  // Initial position in x (semi-major axis)
    double y = 0;    // Initial position in y
    double vx = 0;   // Initial velocity in x
    double vy = sqrt(G * sm / sma);  // Initial velocity in y (based on circular orbital velocity)
    
    // Vector to store the trajectory
    std::vector<std::vector<double>> trajectory;

    // Compute the trajectory over 'np' points
    for (int i = 0; i < np; ++i) {
        // Acceleration due to gravity (Newton's law of gravitation)
        double r = sqrt(x * x + y * y);  // Distance to the star's center
        double ax = -G * sm * x / (r * r * r); // Acceleration in x
        double ay = -G * sm * y / (r * r * r); // Acceleration in y

        // Update velocities and positions using Euler's method
        vx += ax * 0.01;  // Small time step (dt = 0.01)
        vy += ay * 0.01;
        x += vx * 0.01;
        y += vy * 0.01;

        // Store positions in the trajectory
        trajectory.push_back({x, y});
    }

    return trajectory;
}

// Function to plot the trajectory of the planet
void plot_trajectory(const std::vector<double>& x_vals, const std::vector<double>& y_vals) {
    // Plot the trajectory of the planet around the star (2D)
    plt::plot(x_vals, y_vals, "*");  // Plot using the generated trajectory data

    // Customize the plot
    plt::title("Planet's Trajectory Around a Star");
    plt::xlabel("X Position (meters)");
    plt::ylabel("Y Position (meters)");
    plt::show();
}

int main() {
    // Input data: You can randomize these inputs to simulate different scenarios
    double mass = 5.972e24;             // Mass of Earth (kg)
    double star_mass = 1.989e30;        // Mass of the star (kg)
    double semi_major_axis = 1.496e11;  // Semi-major axis of the orbit (avg distance from Earth to Sun in meters)
    double num_points = 1000;           // Number of points to calculate for the orbit

    // Get the planet's trajectory using Newton's law of gravitation
    std::vector<std::vector<double>> trajectory = newtons_law(mass, star_mass, semi_major_axis, num_points);
    
    // Vectors to store x and y positions for plotting
    std::vector<double> x_vals, y_vals;
    
    // Fill vectors with the trajectory data
    for (const auto& point : trajectory) {
        x_vals.push_back(point[0]);
        y_vals.push_back(point[1]);
    }

    // Call the plot function
    plot_trajectory(x_vals, y_vals);

    // Show the first 10 points of the trajectory in the console for inspection
    cout << "First 10 points of the trajectory:" << endl;
    for (int i = 0; i < 10 && i < trajectory.size(); ++i) {
        cout << "Point " << i + 1 << ": x = " << trajectory[i][0] << ", y = " << trajectory[i][1] << endl;
    }

    return 0;
}
