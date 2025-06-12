#pragma once
#include "../IPage.hpp"
#include "component/LabeledSlider.hpp"
#include <memory>

namespace ui {

    class SettingsPage : public IPage {
    private:
        // 私有构造函数，防止外部直接创建实例
        SettingsPage() = default;

        // --- 此页面特有的控件句柄 ---
        lv_obj_t *m_title_label = nullptr;
        lv_obj_t *m_info_label = nullptr;
        lv_obj_t *m_settings_button = nullptr;

        // --- 此页面具有的组件 ---
        std::unique_ptr<LabeledSlider> m_volume_slider;

    public:
        // 禁止拷贝和赋值
        SettingsPage(const SettingsPage &) = delete;
        SettingsPage &operator=(const SettingsPage &) = delete;

        // 获取单例实例的静态方法
        static SettingsPage &instance();

        // --- 实现基类的纯虚函数 ---
        const char *getName() const override { return "SettingsPage"; }
        void initWidgets() override;
        void destroyWidgets() override;

    private:
        // 私有的事件回调等
        static void on_home_button_clicked(lv_event_t *e);
    };

} // namespace ui
