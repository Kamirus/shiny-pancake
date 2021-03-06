#include "World.hpp"
#include "Entities/Basic.hpp"

std::vector<std::shared_ptr<GameObject>>
World::getObjectsInRadius(float x, float y, float radius) {
  std::vector<std::shared_ptr<GameObject>> result;
  for (auto& object : objects) {
    float disX = object->x - x;
    float disY = object->y - y;
    if (disX * disX + disY * disY < radius * radius) {
      result.push_back(object);
    }
  }
  return result;
}

std::vector<std::shared_ptr<Bullet>> World::getBulletsInRadius(float x,
                                                               float y,
                                                               float range,
                                                               unsigned team) {
  std::vector<std::shared_ptr<Bullet>> result;
  for (auto& object : objects) {
    auto unit = std::dynamic_pointer_cast<Bullet>(object);
    if (unit != nullptr) {
      float disX = object->x - x;
      float disY = object->y - y;
      if (disX * disX + disY * disY <= range * range && unit->team != team) {
        result.push_back(unit);
      }
    }
  }
  return result;
}

std::vector<std::shared_ptr<Basic>>
World::getAlliedObjectsInRadius(float x, float y, float radius, unsigned team) {
  std::vector<std::shared_ptr<Basic>> result;
  for (auto& object : objects) {
    auto unit = std::dynamic_pointer_cast<Basic>(object);
    if(unit != nullptr)
    {
      float disX = object->x - x;
      float disY = object->y - y;
      if (disX * disX + disY * disY < radius * radius && unit->team == team && unit->type != "Spawner") {
        result.push_back(unit);
      }
    }
  }
  return result;
}

std::shared_ptr<Basic> World::getNearestUnit(float x,
                                             float y,
                                             float range,
                                             unsigned team) {
  float minDis = 1000000;
  std::shared_ptr<Basic> result = nullptr;
  for (auto& object : objects) {
    auto unit = std::dynamic_pointer_cast<Basic>(object);
    if (unit != nullptr) {
      float disX = object->x - x;
      float disY = object->y - y;
      float dis = disX * disX + disY * disY;
      if (dis < minDis && dis <= range * range && unit->team != team) {
        minDis = disX * disX + disY * disY;
        result = unit;
      }
    }
  }
  return result;
}

std::shared_ptr<Basic> World::collidesWithUnit(float x,
                                               float y,
                                               unsigned team) {
  for (auto& object : objects) {
    auto unit = std::dynamic_pointer_cast<Basic>(object);
    if (unit != nullptr) {
      float disX = object->x - x;
      float disY = object->y - y;
      float dis = disX * disX + disY * disY;
      if (dis < unit->size * unit->size && unit->team != team) {
        return unit;
      }
    }
  }
  return nullptr;
}

void World::setDistressCall(float x, float y, float range, unsigned team) {
  float minDis = 1000000;
  std::shared_ptr<Basic> result = nullptr;
  for (auto& object : objects) {
    auto unit = std::dynamic_pointer_cast<Basic>(object);
    if (unit != nullptr) {
      float disX = object->x - x;
      float disY = object->y - y;
      float dis = disX * disX + disY * disY;
      if (dis < minDis && dis <= range * range && unit->team == team &&
          unit->x != x && unit->y != y) {
        minDis = disX * disX + disY * disY;
        result = unit;
      }
    }
  }
  if (result != nullptr) {
    if (result->type != "Spawner") {
      result->vx = x - result->x;
      result->vy = y - result->y;
    }
  }
}
