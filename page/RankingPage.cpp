#include "RankingPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>
#include <QCoreApplication>
//cst的排名界面，在构造函数中创建了排名界面，包括了排名表格，返回按钮，标题，刷新按钮，清空按钮，并设置了信号与槽的连接
//界面生成后，会调用loadRankings()函数，加载排行榜，并显示在排名表格中
//用rankingFilePath()函数，获取排行榜文件的路径，用loadRankings()函数，加载排行榜，并显示在排名表格中
//用onRefreshClicked()函数，接收刷新按钮点击信号，并调用loadRankings()函数，刷新排行榜
//用onClearClicked()函数，接收清空按钮点击信号，并调用saveRankings()函数，清空排行榜
//用onUpdateScoreRankings(QString name, int score)函数，接收更新分数信号，并调用saveRankings()函数，保存排行榜
//用saveRankings()函数，保存排行榜，并用QFile对象，打开排行榜文件，用QTextStream对象，写入排行榜文件内容
//用loadRankings()函数，加载排行榜，并用QFile对象，打开排行榜文件，用QTextStream对象，读取排行榜文件内容
//用std::sort()函数，按分数降序排序排行榜，用QList<QList<QString>>存储每行的字符串，用QStringList对象，把line分割成name,score,datetime三个字符串，用”,”分割，并去掉两端空格
//用QTableWidgetItem对象，设置排名表格的每一行的文本，用QTableWidget对象，设置排名表格的一些属性，比如行数、列数、行宽、列宽、行高、列高、选中方式、选中模式等

RankingPage::RankingPage(QWidget *parent) : QWidget(parent){
    //添加标题
    titleLabel = new QLabel("Ranking", this);
    //取到标题的字体为titleFont
    QFont titleFont = titleLabel->font();
    //设置字体大小为18
    titleFont.setPointSize(18);
    //设置字体为粗体
    titleFont.setBold(true);
    //设置标题的字体为titleFont
    titleLabel->setFont(titleFont);
    //设置标题的对齐方式为居中
    titleLabel->setAlignment(Qt::AlignCenter);

    //添加表格
    table = new QTableWidget(this);
    //设置表格的列数为4
    table->setColumnCount(4);
    //设置表格头部标签
    //创建QList<QString> headers; //QList 是 Qt 内置的类，用于存储字符串的列表
    //headers << "Rank" << "Name" << "Score" << "Date"; //初始化headers列表，就是把这些字符串放入headers列表中
    QStringList headers;
    headers << "Rank" << "Name" << "Score" << "Date";
    //设置表格头部标签为headers
    table->setHorizontalHeaderLabels(headers);
    //设置table的一些属性，比如行数、列数、行宽、列宽、行高、列高、选中方式、选中模式等
    //不懂就说是ai写的，不用管，直接跳过
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QTableWidget::NoEditTriggers);
    table->setSelectionBehavior(QTableWidget::SelectRows);
    table->setSelectionMode(QTableWidget::SingleSelection);

    //添加按钮
    //添加返回按钮
    backButton = new QPushButton("Back", this);
    //添加刷新按钮
    refreshButton = new QPushButton("Refresh", this);
    //添加清空按钮
    clearButton = new QPushButton("Clear", this);

    //接收返回按钮点击信号，并发射信号backButtonClicked()，接收函数由后端做处理
    connect(backButton, &QPushButton::clicked, this, [this](){
        emit backButtonClicked();
    });
    //接收刷新按钮点击信号，并调用onRefreshClicked()，接收函数由后端做处理
    connect(refreshButton, &QPushButton::clicked, this, &RankingPage::onRefreshClicked);
    //接收清空按钮点击信号，并调用onClearClicked()，接收函数由后端做处理
    connect(clearButton, &QPushButton::clicked, this, &RankingPage::onClearClicked);

    //创建水平布局
    QHBoxLayout *topLayout = new QHBoxLayout();
    //添加返回按钮、标题、刷新按钮、清空按钮
    //返回按钮左对齐，标题居中
    topLayout->addWidget(backButton, 0, Qt::AlignLeft);
    //添加空格
    topLayout->addStretch();
    //添加标题，标题居中
    topLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    //添加空格
    topLayout->addStretch();
    //添加刷新按钮，右对齐
    topLayout->addWidget(refreshButton, 0, Qt::AlignRight);
    //添加清空按钮，右对齐
    topLayout->addWidget(clearButton, 0, Qt::AlignRight);

    //创建垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    //添加顶部布局到垂直布局，顶部布局就是topLayout,就是上面的什么返回按钮，标题，刷新按钮，清空按钮
    //垂直布局会自动拉伸，以适应表格的大小
    mainLayout->addLayout(topLayout);
    //添加表格到垂直布局
    mainLayout->addWidget(table);
    //设置布局为垂直布局，就是mainLayout
    setLayout(mainLayout);

    //加载排行榜
    loadRankings();
}

//返回排行榜文件的路径
QString RankingPage::rankingFilePath(){
    //获取程序运行目录
    QString dir = QCoreApplication::applicationDirPath();
    //拼接排行榜文件的路径
    return dir + "/rankings.txt";
}

    //加载排行榜
void RankingPage::loadRankings(){
    //设置表格的行数为0
    table->setRowCount(0);
    //打开排行榜文件，rankingFilePath()函数返回排行榜文件的路径
    QFile file(rankingFilePath());
    //如果文件不存在，则创建5行空白行
    if(!file.exists()){
        // show placeholder rows
        //设置表格的行数为5
        table->setRowCount(5);
        //用for循环，设置表格的第i行的第j列的文本为"--"
        for(int i=0;i<5;i++){
            table->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
            table->setItem(i, 1, new QTableWidgetItem("--"));
            table->setItem(i, 2, new QTableWidgetItem("0"));
            table->setItem(i, 3, new QTableWidgetItem("--"));
        }
        return;
    }

    //读取排行榜文件，如果文件不存在或读取失败，则返回
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    //读取排行榜文件内容，传入file的指针，并用QTextStream对象
    QTextStream in(&file);
    //读取排行榜文件内容，并用QList<QList<QString>>存储每行的字符串
    QList<QList<QString>> rows;
    //用while循环，读取排行榜文件内容，直到文件结束,in.atEnd()就是判断文件是否结束，返回true表示到达文件最底部，返回false表示还没到文件最底部
    while(!in.atEnd()){
        //读取一行内容，并去掉两端空格，付给line
        QString line = in.readLine().trimmed();
        //如果行为空，则跳过
        if(line.isEmpty()) continue;
        // expect CSV: name,score,datetime
        //用QStringList对象，把line分割成name,score,datetime三个字符串，用”,”分割，并去掉两端空格
        QStringList parts = line.split(',');
        //如果parts的长度小于2，则跳过
        if(parts.size() < 2) continue;
        //把name,score,datetime三个字符串放入QList<QString>对象中，并加入rows列表
        //取到第0个元素，也就是name字符串，去掉两端空格
        QString name = parts.value(0).trimmed();
        //取到第1个元素，也就是score字符串，去掉两端空格
        QString score = parts.value(1).trimmed();
        //取到第2个元素，也就是datetime字符串，去掉两端空格
        QString date = parts.value(2).trimmed();
        //把name,score,datetime三个字符串并加入rows列表
        rows.append({name, score, date});
    }
    //关闭排行榜文件
    file.close();

    // sort by score descending
    // 按分数降序排序
    // 用C++标准库中的sort函数，传入rows列表，并用lambda表达式，按分数降序排序
    std::sort(rows.begin(), rows.end(), [](const QList<QString>& a, const QList<QString>& b){
        bool ok1, ok2;
        int s1 = a.value(1).toInt(&ok1);
        int s2 = b.value(1).toInt(&ok2);
        if(!ok1) s1 = 0;
        if(!ok2) s2 = 0;
        return s1 > s2;
    });

    // 设置表格的行数为rows的长度
    int r = rows.size();
    table->setRowCount(r);
    //用for循环，设置表格的第i行的第j列的文本为rows[i][j]
    for(int i=0;i<r;i++){
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
        table->setItem(i, 1, new QTableWidgetItem(rows[i].value(0)));
        table->setItem(i, 2, new QTableWidgetItem(rows[i].value(1)));
        table->setItem(i, 3, new QTableWidgetItem(rows[i].value(2)));
    }
}

    //接收刷新按钮点击信号，并调用loadRankings()，刷新排行榜
void RankingPage::onRefreshClicked(){
    loadRankings();
}

// 接收清空按钮点击信号，并调用onClearClicked()，清空排行榜
void RankingPage::onClearClicked(){
    QString path = rankingFilePath();
    QFile file(path);
    if(file.exists()){
        file.remove();
    }
    loadRankings();
}

// 保存排行榜，游戏结束更新分数时调用，
void RankingPage::saveRankings(){
    // Not used by UI currently, implemented for completeness
    // 排行榜文件路径
    QFile file(rankingFilePath());
    // 如果文件不存在，则return返回,不保存
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    //创建QTextStream对象，传入file的指针，并用QTextStream对象
    QTextStream out(&file);
    //用for循环，遍历表格的每一行，并把每一行的name,score,date三个字符串写入排行榜文件
    int rows = table->rowCount();
    for(int i=0;i<rows;i++){
        // 取到第i行的第1列的文本，也就是name字符串,用?:运算符判断是否为空,如果table->item(i,1)为空，则返回空字符串，否则返回table->item(i,1)->text()
        QString name = table->item(i,1) ? table->item(i,1)->text() : "";
        // 取到第i行的第2列的文本，也就是score字符串,用?:运算符判断是否为空,如果table->item(i,2)为空，则返回0，否则返回table->item(i,2)->text()
        QString score = table->item(i,2) ? table->item(i,2)->text() : "0";
        // 取到第i行的第3列的文本，也就是date字符串，用?:运算符判断是否为空,如果table->item(i,3)为空，则返回当前日期时间，否则返回table->item(i,3)->text()
        QString date = table->item(i,3) ? table->item(i,3)->text() : QDateTime::currentDateTime().toString();
        // 用out写入排行榜文件，用name,score,date三个字符串，用”,”分割，并换行
        out << name << "," << score << "," << date << "\n";
    }
    //关闭排行榜文件
    file.close();
}

// 接收游戏结束信号，并调用onUpdateScoreRankings()，更新排行榜，后端写的
void RankingPage::onUpdateScoreRankings(QString name, int score){
    // update score and date
    int rows = table->rowCount();
    bool updated = false;
    for(int i=0;i<rows;i++){
        if(table->item(i,1)->text() == name){
            table->setItem(i, 2, new QTableWidgetItem(QString::number(score)));
            table->setItem(i, 3, new QTableWidgetItem(QDateTime::currentDateTime().toString()));
            updated = true;
            break;
        }
    }
    if(!updated){
        // add new row
        table->insertRow(0);
        table->setItem(0, 0, new QTableWidgetItem("1"));
        table->setItem(0, 1, new QTableWidgetItem(name));
        table->setItem(0, 2, new QTableWidgetItem(QString::number(score)));
        table->setItem(0, 3, new QTableWidgetItem(QDateTime::currentDateTime().toString()));
    }
    for(int i=0;i<rows;i++){
        table->item(i,0)->setText(QString::number(i+1));
    }
    // sort by score descending
    for(int i=0;i<rows-1;i++){
        for(int j=i+1;j<rows;j++){
            bool ok1, ok2;
            int s1 = table->item(i,2)->text().toInt(&ok1);
            int s2 = table->item(j,2)->text().toInt(&ok2);
            if(!ok1) s1 = 0;
            if(!ok2) s2 = 0;
            if(s1 < s2){
                // swap rows
                table->insertRow(i);
                // table->setRow(i, table->takeRow(j));
                table->removeRow(j);
                break;
            }
        }
    }
    // save to file
    saveRankings();
    
}

//后端写的
void RankingPage::changeLanguage(QString lang){
    if(lang == "en"){
        titleLabel->setText("Ranking");
        backButton->setText("Back");
        refreshButton->setText("Refresh");
        clearButton->setText("Clear");
        QStringList headers;
        headers << "Rank" << "Name" << "Score" << "Date";
        table->setHorizontalHeaderLabels(headers);
    }else if(lang == "zh"){
        titleLabel->setText("排行榜");
        backButton->setText("返回");
        refreshButton->setText("刷新");
        clearButton->setText("清空");
        QStringList headers;
        headers << "排名" << "姓名" << "分数" << "日期";
        table->setHorizontalHeaderLabels(headers);
    }
}