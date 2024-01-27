# 活动冲突检测系统

> 活动冲突检测系统是一个基于 Qt （c++）的应用程序，用于管理和监测活动安排的时间冲突。


## 成果展示

![image-20240122123742682](../../Jaxi-Jiang-Blog/source/images/readme/image-20240122123742682.png)

# :arrow_forward:功能成果展示

## 功能要求及说明

> 编写一个程序完成活动冲突检测系统，能够录入、修改、删除活动信息，通过对活动时间的检测，提醒活动之间安排的冲突。

1. **活动信息**：活动信息包括开始时间、结束时间、活动内容和参与人员，通过结构体的方式进行表达。
2. **文件加载**：通过菜单方式从文件（如 `act.txt`）加载已录入的活动信息。
3. **活动管理**：通过菜单新增、修改、删除活动安排。
4. **冲突检测**：载入文件中的活动信息后，与内存中已存储的活动信息进行时间比较，检测并提示存在冲突的活动。
5. **数据保存**：提供将所有日程信息保存回文件的功能，以便再次载入内存。
6. **模块化设计**：系统采用模块化设计，其中冲突检测模块具有复用性。
7. **增加功能**： 活动列表的**清除按钮**和冲突列表的**清除按钮**。



# :book:代码介绍

## 项目结构
```markdown
# Qt 项目文件
├── ActivityConflictChecker.pro 
├── main.cpp # 程序入口点
├── MainWindow/ # 主窗口模块
│ ├── mainwindow.ui # 主窗口的 UI 设计
│ ├── mainwindow.cpp # 主窗口的按钮实现
│ └── mainwindow.h # 主窗口的头文件
│
├── Activity/ # 活动相关的模块
│ ├── activity.cpp # 活动类的实现，以及对应后端接口实现
│ └── activity.h # 活动类的定义，以及对应后端接口定义
```
## 模块设计

### 1. `MainWindow` 前端模块

- **文件位置**：`MainWindow/` 目录（包括 `mainwindow.ui`, `mainwindow.cpp`, `mainwindow.h`）
- 对应功能
  - **文件加载**：通过主窗口的菜单实现从文件（如 `act.txt`）加载活动信息。
  - **活动管理**：通过主窗口的菜单实现录入、修改、重新加载，冲突检测等等按钮的界面交互。
- 具体功能
  - `mainwindow.ui`要有 **退出键**，**全屏**，**缩小**， **主菜单标签**， **录入按钮**， **修改按钮**， **重新加载按钮**， **检测冲突按钮**， **活动列表表单**， **冲突信息表单** ，以及两个对应的**清除按钮**。
  - `mainwindow.cpp`: 调用后端的逻辑处理函数。
  - 具体函数
    - **构造函数和析构函数：**
      - `MainWindow(QWidget *parent)`：构造函数初始化主窗口。
      - `~MainWindow()`：析构函数释放内存。
    - **文件加载相关函数：**
      - `on_loadButton_clicked()`：通过文件对话框选择文件，调用后端接口加载活动信息，然后在界面上展示。
      - `on_editButton_clicked()`：通过文件对话框选择文件，调用系统接口打开文件夹。
    - **重新加载按钮相关函数：**
      - `on_reloadButton_clicked()`：与加载按钮类似，但先清空原有列表再加载新活动列表。
    - **冲突检测相关函数：**
      - `on_detectButton_clicked()`：遍历活动列表，调用后端接口检测冲突，更新活动列表和冲突列表。
    - **清除按钮相关函数：**
      - `on_actcleanButton_clicked()`：清空活动列表。
      - `on_concleanButton_clicked()`：清空冲突列表。


### 2. `Activity` 后端模块

- **文件位置**：`Activity/` 目录（包括 `activity.cpp`, `activity.h`）
- 对应功能
  - **活动信息**：定义一个类 `Activity`，用于表示**录入、修改**活动的信息（开始时间、结束时间、活动内容、参与人员）。
  - 若干成员函数
    - **`loadActivitiesFromFile` 函数：**
      - 输入参数：文件路径 `filePath`（QString 类型）
      - 输出：QListActivity::activity，包含从文件中加载的活动列表。
      - 功能：从指定文件中读取活动信息，创建并返回一个包含这些活动的 QList。
    - **`parseActivity` 函数：**
      - 输入参数：字符串 `line`（QString 类型）
      - 输出：Activity::activity 类型，表示从字符串解析得到的活动。
      - 功能：将输入的字符串解析为活动信息，返回对应的活动对象。
    - **`showActivitiesList` 函数：**
      - 输入参数：活动列表 `activities`（QListActivity::activity 类型）、UI指针 `ui`（Ui::MainWindow 类型指针）
      - 输出：无
      - 功能：将活动列表显示到主窗口的活动列表部件中。
    - **`stringActivity` 函数：**
      - 输入参数：活动 `act`（Activity::activity 类型）
      - 输出：QString 类型，表示活动信息的字符串表示。
      - 功能：将活动对象转换为字符串表示，便于显示或存储。
    - **`hasConflict` 函数：**
      - 输入参数：两个活动 `a` 和 `b`（Activity::activity 类型）
      - 输出：bool 类型，表示是否存在冲突。
      - 功能：检测两个活动的时间是否有重叠，如果有则返回 true，表示存在冲突。

### 3. 其他文件

- **`ActivityConflictChecker.pro`**：Qt 项目文件，定义了项目的整体配置，如包含的文件和模块。
- **`main.cpp`**：程序的入口点，用于初始化和启动主窗口。

## 编译和运行

1. 使用 Qt Creator 打开 `ActivityConflictChecker.pro` 文件。
2. 选择合适的编译器进行构建。
3. 运行程序。

