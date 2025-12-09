#include "SettingPage.h"
#include "qnamespace.h"
#include "qtmetamacros.h"

//blx的设置界面
//在构造函数中初始化控件，设置布局，连接信号槽
//设置语言，设置音量，设置主题
//当点击返回按钮时，发射返回按钮点击信号，由后端设置并连接到主窗口的返回按钮点击槽函数
//当音量滑块变化时，发射音量变化信号，由后端设置并连接到主窗口的音量变化槽函数
//当语言下拉框变化时，调用setLanguage()函数设置语言，并发射语言变化信号，由后端设置并连接到主窗口的语言变化槽函数
//当主题下拉框变化时，发送themeChanged信号，由后端设置并连接到主窗口的主题变化槽函数


SettingPage::SettingPage(QTranslator *translator, QWidget *parent)
    : QWidget(parent), m_translator(translator) {
    // 设置窗口属性
    setWindowTitle(tr("setting"));

    // 初始化控件
    //创建返回按钮
    backButton = new QPushButton(tr("Back"), this);

    //创建音量显示标签和滑块
    volumeLabel = new QLabel("Volume", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    //创建语言显示标签和下拉框
    langLabel = new QLabel("Language", this);
    langCombo = new QComboBox(this);
    //创建主题显示标签和下拉框
    themeLabel = new QLabel(tr("Theme"), this);
    themeCombo = new QComboBox(this);

    // 设置控件大小
    //设置音量标签大小
    volumeLabel->setFixedSize(300, 40);
    //设置音量滑块大小
    volumeSlider->setFixedSize(300, 40);
    //设置语言标签大小
    langCombo->setFixedSize(300, 40);
    //设置主题标签大小
    langLabel->setFixedSize(300, 40);
    //设置主题下拉框大小
    themeCombo->setFixedSize(300, 40);
    //设置返回按钮大小
    themeLabel->setFixedSize(300, 40);


    // 配置音量滑块
    // 音量范围为0-100，默认值为50
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50); // 默认音量50%

    // 配置语言下拉框（支持中、英）
    // 为语言下拉框添加中、英选项
    langCombo->addItem(tr("English"), "en");
    langCombo->addItem(tr("中文"), "zh");

    // 配置主题下拉框（支持浅色、深色）
    //为主题下拉框添加light
    themeCombo->addItem("light","light");
    //为主题下拉框添加dark
    themeCombo->addItem("dark","dark");

    // 布局管理
    QVBoxLayout *layout = new QVBoxLayout(this);

    //添加语言下拉框、主题下拉框、音量滑块、返回按钮到布局中
    //语言标签，拉伸度为0，居中
    layout->addWidget(langLabel, 0, Qt::AlignCenter);
    //语言下拉框，拉伸度为0，居中
    layout->addWidget(langCombo, 0, Qt::AlignCenter);
    //添加空格
    layout->addSpacing(20);
    //主题标签，拉伸度为0，居中
    layout->addWidget(volumeLabel, 0, Qt::AlignCenter);
    //音量滑块，拉伸度为0，居中
    layout->addWidget(volumeSlider, 0, Qt::AlignCenter);
    //添加空格
    layout->addSpacing(20);
    //主题标签，拉伸度为0，居中
    layout->addWidget(themeLabel, 0, Qt::AlignCenter);
    //主题下拉框，拉伸度为0，居中
    layout->addWidget(themeCombo, 0, Qt::AlignCenter);
    //添加空格
    layout->addStretch();
    //返回按钮，拉伸度为0，居中
    layout->addWidget(backButton, 0, Qt::AlignCenter);



    // 连接信号槽
    // 接收backbutton点击信号，调用onBackButtonClicked()函数
    connect(backButton, &QPushButton::clicked, this, &SettingPage::onBackButtonClicked);
    // 接收音量滑块变化信号，调用volumeChanged()函数
    connect(volumeSlider, &QSlider::valueChanged, this, &SettingPage::volumeChanged);
    // 接收语言下拉框变化信号，调用onLangComboChanged()函数
    connect(langCombo, &QComboBox::currentIndexChanged, this, &SettingPage::onLangComboChanged);
    // 接收语言变化信号，调用setLanguage()函数
    connect(this, &SettingPage::languageChanged, this, &SettingPage::setLanguage);
    //QSlider变化会发出valueChanged信号,接收音量变化信号，发送volumeChanged信号
    connect(volumeSlider, &QSlider::valueChanged, [=](int value) {
        emit volumeChanged(value/100.0);
    });
    // 接收主题下拉框变化信号，发送themeChanged信号
    connect(themeCombo, &QComboBox::currentIndexChanged, [=](int index) {
        //返回当前选择的主题的名称QString字符串
        QString theme = themeCombo->itemData(index).toString();
        //发送themeChanged信号
        emit themeChanged(theme);
    });
}

// 返回按钮点击：发射返回信号
void SettingPage::onBackButtonClicked() {
    // 发射返回按钮点击信号
    emit backButtonClicked();
}

// 语言选择变化：发射语言变化信号
void SettingPage::onLangComboChanged(int index) {
    // 获取当前选择的语言的名称QString字符串
    QString lang = langCombo->itemData(index).toString();
    // 调用setLanguage()函数设置语言，并发射语言变化信号
    setLanguage(lang);
    // 发射语言变化信号
    emit languageChanged(lang);
}

//后端写的
void SettingPage::setLanguage(const QString &lang) {
    if(lang == "zh"){
        backButton->setText(tr("返回主界面"));
        langLabel->setText(tr("语言"));
        volumeLabel->setText(tr("音量"));
        themeLabel->setText(tr("主题"));
        themeCombo->setItemText(0,tr("浅色"));
        themeCombo->setItemText(1,tr("深色"));
        this->setWindowTitle(tr("设置"));

    }else if(lang == "en"){
        backButton->setText(tr("Back"));
        langLabel->setText(tr("Language"));
        volumeLabel->setText(tr("Volume"));
        themeLabel->setText(tr("Theme"));
        themeCombo->setItemText(0,tr("light"));
        themeCombo->setItemText(1,tr("dark"));
        this->setWindowTitle(tr("Setting"));
    }
}