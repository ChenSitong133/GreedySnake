#include "SettingPage.h"
#include "qnamespace.h"

SettingPage::SettingPage(QTranslator *translator, QWidget *parent)
    : QWidget(parent), m_translator(translator) {
    // 设置窗口属性
    setWindowTitle(tr("设置"));
    setFixedSize(400, 300);

    // 初始化控件
    backButton = new QPushButton(tr("返回主界面"), this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    langCombo = new QComboBox(this);

    // 配置音量滑块
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50); // 默认音量50%

    // 配置语言下拉框（支持中、英、日、韩）
    langCombo->addItem(tr("中文"), "zh");
    langCombo->addItem(tr("English"), "en");
    langCombo->addItem(tr("日本語"), "ja");
    langCombo->addItem(tr("한국어"), "ko");

    // 布局管理
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(tr("语言设置"), this));
    layout->addWidget(langCombo);
    layout->addSpacing(20);
    layout->addWidget(new QLabel(tr("音量设置"), this));
    layout->addWidget(volumeSlider);
    layout->addStretch();
    layout->addWidget(backButton, 0, Qt::AlignCenter);

    // 连接信号槽
    connect(backButton, &QPushButton::clicked, this, &SettingPage::onBackButtonClicked);
    connect(volumeSlider, &QSlider::valueChanged, this, &SettingPage::volumeChanged);
    connect(langCombo, &QComboBox::currentIndexChanged, this, &SettingPage::onLangComboChanged);
}

// 返回按钮点击：发射返回信号
void SettingPage::onBackButtonClicked() {
    emit backButtonClicked();
}

// 语言选择变化：发射语言变化信号
void SettingPage::onLangComboChanged(int index) {
    QString lang = langCombo->itemData(index).toString();
    emit languageChanged(lang);
}
