# Assignment 1: Sports Complex Planning

## Goal
The goal of this assignment is to formulate and solve a complex problem using search techniques. By formulating the problem as a search, we aim to find optimal solutions or good approximations using heuristic or local search algorithms.

## Scenario
We are tasked with optimizing the layout of a new sports complex in Delhi to minimize walking time for sports persons and children based on personalized schedules. The complex comprises various zones, each dedicated to a specific type of sport or activity. Users have personalized schedules dictating when they visit each zone. Our objective is to assign zones to locations within the complex to minimize the average walking time between zones.

## Problem Statement
Given the layout of the sports complex, represented by matrices indicating walking times between locations and frequency of visits between zones, our task is to allocate zones to locations such that the total walking time is minimized.

### Input
- Total processing time available
- Number of zones (z)
- Number of locations (l)
- Matrix N representing daily walks between zones
- Matrix T representing walking times between locations

### Output
The algorithm should return the best allocation of zones to locations, ensuring each location hosts only one zone. The output format is a sequence of z unique numbers, each representing the location assigned to a zone.

## Basic Algorithms Implemented

1. Local Search with random restart: Implement a neighbor function and local search algorithm to iteratively improve solutions.

