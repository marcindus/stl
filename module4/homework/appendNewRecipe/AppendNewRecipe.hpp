#pragma once

#include <deque>
#include <list>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

std::stringstream FormatRecipit(std::vector<std::string> steps,
                                const std::list<std::string>& ingredients,
                                const std::deque<std::pair<size_t, char>>& amount);

std::vector<std::string> FormatIngredients(const std::list<std::string>& ingredients,
                                          const std::deque<std::pair<size_t, char>>& amount);

bool AppendNewRecipe(std::vector<std::string> steps,
                     const std::list<std::string> &ingredients,
                     const std::deque<std::pair<size_t, char>> &amount);
