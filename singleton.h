/**
 * @Author: YunKai Xia
 * @Date:   2023-08-26 16:31:03
 * @Last Modified by:   YunKai Xia
 * @Last Modified time: 2023-08-26 17:50:27
 */
#include <stdint.h>

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template <class T>
T* Singleton(){
    static T instance;
    return &instance;
}

#endif /* __SINGLETON_H__ */
