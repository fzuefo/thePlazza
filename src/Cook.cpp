/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** nico code
*/

#include "Cook.hpp"
#include <memory>

namespace Plazza
{
    static std::mutex acces_mutex;

    Cook_manager::Cook_manager(unsigned int maxCooks, unsigned int reloadTime, double mul)
    {
        _max = maxCooks;
        _reload = reloadTime;
        _mul = mul;
        _item = {5,5,5,5,5,5,5,5,5};
        _elaps = 0;
        _delta = 0;
        _isActive = false;
    }

    Cook_manager::~Cook_manager()
    {
        _isActive = true;
        for (auto &it: _Cook) {
            it.join();
        }
    }

    void Cook_manager::chec_cookActive()
    {
        auto it1 = _Cook.begin();
        auto it2 = _delta_t.begin();

        for (size_t i = 0; i < _Cook.size(); i++) {
            if (_Cook[i].joinable() == true && *_delta_t[i].get() < 0) {
                advance(it1, i);
                advance(it2, i);
                _Cook[i].join();
                _Cook.erase(it1);
                _delta_t.erase(it2);
            }
        }
    }

    std::vector<Plazza::Pizza> Cook_manager::update(float time)
    {
        std::lock_guard<std::mutex> guard(acces_mutex);
        std::vector<Plazza::Pizza> vec = std::move(this->_cooked_pizza_id);

        _elaps = time * 10;
        _delta += _elaps;
        for (size_t i = 0; i != _delta_t.size(); i++)
            *_delta_t[i].get() += _elaps;
        if (_delta >= _reload / 1000) {
            _delta -= _reload / 1000;
            this->add_ingredient();
        }
        this->chec_cookActive();
        return vec;
    }

    void Cook_manager::add_ingredient()
    {
        this->_item.doe++;
        this->_item.tomato++;
        this->_item.gruyer++;
        this->_item.ham++;
        this->_item.mushroom++;
        this->_item.steak++;
        this->_item.goat++;
        this->_item.egg++;
        this->_item.love++;
    }

    bool Cook_manager::isFull()
    {
        if (_Cook.size() >= _max)
            return true;
        return false;
    }

    bool Cook_manager::manag_pizza(Plazza::Pizza piza)
    {
        if (_Cook.size() >= _max)
            return false;
        add_pizza(piza);
        return true;
    }
/*
    void Cook_manager::itemManager(Plazza::Pizza &piza)
    {
        std::lock_guard<std::mutex> guard(acces_mutex);

        while (piza.getComponant(this->_item) == false || this->_isActive == true) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
        }*/

    void Cook_manager::add_pizza(Plazza::Pizza piza)
    {
        std::shared_ptr<float> ptr = std::make_shared<float>(0.f);
        std::shared_ptr<Plazza::Pizza> pizza = std::make_shared<Plazza::Pizza>(piza);

        _delta_t.push_back(ptr);
        _Cook.push_back(std::thread([this, pizza, ptr](){
            acces_mutex.lock();
            while (pizza->getComponant(this->_item) == false || this->_isActive == true) {
                acces_mutex.unlock();
                std::this_thread::sleep_for(std::chrono::seconds(5));
                acces_mutex.lock();
            }
            acces_mutex.unlock();
            while (pizza->time() * this->_mul > *ptr.get() || this->_isActive == true) {
            }
            std::lock_guard<std::mutex> guard(acces_mutex);
            *ptr.get() = -1;
            this->_cooked_pizza_id.push_back(*pizza.get());
        })
       );
    }

    unsigned int Cook_manager::getNbActiveCooks() const
    {
        return this->_Cook.size();
    }
}
