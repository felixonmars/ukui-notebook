/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/

#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include <QListView>
#include <QScrollArea>

#include <QMenu>
#include <QAction>

class NoteMenu : public QMenu
{
    Q_OBJECT
public:
    explicit NoteMenu(QWidget* parent = nullptr);
    QModelIndex getIndex(){return m_index;}
    void setIndex(QModelIndex index){m_index = index;}
private:
    QModelIndex m_index;
};

class NoteView : public QListView
{
    Q_OBJECT

    friend class tst_NoteView;  //友元类 class tst_NoteView可以访问此类NoteView的private和protected成员变量

public:
    explicit NoteView(QWidget* parent = Q_NULLPTR);
    ~NoteView();

    void animateAddedRow(const QModelIndex &parent, int start, int end);
    void animateRemovedRow(const QModelIndex &parent, int start, int end);
    void setAnimationEnabled(bool isEnabled);
    void setCurrentRowActive(bool isActive);

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) Q_DECL_OVERRIDE;

private:
    bool m_isScrollBarHidden;
    bool m_animationEnabled;
    bool m_isMousePressed;
    int m_rowHeight;

    NoteMenu *m_popMenu = nullptr; //右键弹出菜单
    QMap<QString,QAction*> m_menuActs; //右键动作列表

    void initPopMenu();
    bool addAct(QString);
    void onClearAll();
    void onCreateNew();
    void onTopping(QModelIndex);
    void onDeleteSingle(QModelIndex);
    void onSendMail(QModelIndex);
    void onOpenNote(QModelIndex);

public slots:
    void rowsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd,
                            const QModelIndex &destinationParent, int destinationRow);

    void rowsMoved(const QModelIndex &parent, int start, int end,
                   const QModelIndex &destination, int row);

private slots:
    void init();
    void onCustemMenuRequested(QPoint); //ListView 右键菜单
    void onMenuTriggered(QAction*);
signals:
    void viewportPressed();
    void requestOpenNote(QModelIndex); //打开特定便签页
    void requestDeleteNote(QModelIndex); //删除特定便签页
    void requestCreateNote(); // 新建便签页
    void requestClearAllNotes();//清空便签本
};

#endif // NOTEVIEW_H
