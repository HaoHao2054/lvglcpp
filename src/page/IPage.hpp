#pragma once
#include <string>
#include "lvgl.h"

namespace ui {

    class IPage {
    protected:
        // 每个页面都有一个根容器，此页面上的所有控件都创建在这个容器之上
        lv_obj_t *m_root_container = nullptr;
        bool m_is_initialized = false;

    public:
        // 关键：虚析构函数，允许多态删除
        virtual ~IPage() = default;

        // --- 纯虚函数，定义了每个页面必须实现的接口 ---

        /// @brief 获取页面的唯一名称，用于PageManager注册和查找
        virtual const char *getName() const = 0;

        /// @brief 初始化控件（创建所有lv_obj_t对象）
        virtual void initWidgets() = 0;

        /// @brief 销毁控件（只需删除根容器）
        virtual void destroyWidgets() = 0;

        // --- 普通虚函数，提供默认实现 ---

        /// @brief 显示页面（通常是取消隐藏或执行加载动画）
        virtual void show() {
            if (m_root_container && lv_obj_is_valid(m_root_container)) {
                lv_obj_clear_flag(m_root_container, LV_OBJ_FLAG_HIDDEN);
            }
        }

        /// @brief 隐藏页面
        virtual void hide() {
            if (m_root_container && lv_obj_is_valid(m_root_container)) {
                lv_obj_add_flag(m_root_container, LV_OBJ_FLAG_HIDDEN);
            }
        }

        lv_obj_t *getRoot() const { return m_root_container; }
    };

} // namespace ui
