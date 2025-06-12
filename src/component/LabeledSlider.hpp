#pragma once
#include <cstddef>
#include <functional>
#include <string>
#include "lvgl.h"

class LabeledSlider {
private:
    lv_obj_t *m_container = nullptr; // 组件自身的根容器
    lv_obj_t *m_title_label = nullptr;
    lv_obj_t *m_slider = nullptr;
    lv_obj_t *m_value_label = nullptr;

    std::function<void(int)> m_value_changed_callback;

    // 内部事件回调
    static void on_slider_event(lv_event_t *e);

public:
    // 构造函数必须接收一个父对象
    explicit LabeledSlider(lv_obj_t *parent);
    // 析构函数负责清理自己创建的控件（主要是其根容器）
    ~LabeledSlider();

    // --- 公共API ---
    void setTitle(const std::string &title);
    void align(lv_align_t align, int x_ofs, int y_ofs);
    void setValue(int value);
    int getValue() const;
    void onValueChanged(std::function<void(int)> callback);
    lv_obj_t *getContainer() const { return m_container; } // 方便外部对其进行布局
};
