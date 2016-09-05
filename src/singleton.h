/*
 * AquaEngine
 *Copyright © 2016 Adrien Jeser <adrien@jeser.me>
 *
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AE_SINGLETON_H_
#define AE_SINGLETON_H_

#include <memory>

namespace ae {

template <class T>
class Singleton : public T {
   public:
    Singleton() = default;
    static std::shared_ptr<T> create(bool reset = false) {
        static std::shared_ptr<T> &&instance = nullptr;

        if (instance == nullptr || reset) {
            instance = std::make_shared<T>();
        }

        return instance;
    }

   private:
    /* data */
    Singleton(const T &) = delete;
    Singleton(const T &&) = delete;
};

} /* ae */
#endif /* ifndef AE_SINGLETON_H_ */
