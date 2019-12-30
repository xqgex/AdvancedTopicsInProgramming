/*
 * AlgorithmRegistration.cpp
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Register PlayerAlgorithm implementation
 */

#include <functional>
#include <memory>
#include <iostream>
#include <map>

#include "AlgorithmRegistration.h"
#include "TournamentManager.h"

AlgorithmRegistration::AlgorithmRegistration(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
    TournamentManager::getTournamentManager().registerAlgorithm(id, factoryMethod);
}
