#include "PlaneSlice.h"
#include <QDebug>
//#pragma execution_character_set ("utf-8")

PlaneSlice::PlaneSlice(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    vtkOutputWindow::SetGlobalWarningDisplay(0);


    renderer = vtkSmartPointer<vtkRenderer>::New();  //VTK创建一个新的渲染器对象，用于将图形数据呈现到屏幕上。

    //渲染器对象是VTK中用于渲染图形数据的对象，可用于创建多个视口，每个视口都可以独立地呈现图形数据。
    //渲染器对象被分配给了renderer变量，该变量调用渲染器的方法，如AddActor()和SetBackground()，以将数据添加到渲染器对象并设置背景颜色。
    //渲染器对象添加到渲染窗口中，以便在屏幕上呈现图形数据。


    ui.qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
    renderer->SetBackground(200.0 / 255, 210.0 / 255, 180.0 / 255);
    renderer->Render();
    //GetActiveCamera()方法返回当前激活的相机对象
    renderer->GetActiveCamera()->SetFocalPoint(-150.0, 50.0, .0);
    renderer->GetActiveCamera()->SetPosition(300., 100., 150.);
    renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
    renderer->GetActiveCamera()->SetParallelProjection(1);
    renderer->GetActiveCamera()->SetParallelScale(220);

    // Menu bar
    QMenu* menu_File = ui.menuBar->addMenu(QString(tr("文件")));
    QAction* act_ModelOpen = menu_File->addAction(QString("打开 stl"));
    act_ModelOpen->setIcon(QIcon(":/PlaneSlice/icons/files.png"));
    QAction* act_Clear = menu_File->addAction(QString("清除"));
    act_Clear->setIcon(QIcon(":/PlaneSlice/icons/clear.png"));
    menu_File->addSeparator();
    QAction* act_Settings = menu_File->addAction(QString("裁剪"));
    act_Settings->setIcon(QIcon(":/PlaneSlice/icons/setting.png"));
    QAction* act_posClip = menu_File->addAction(QString("Forward"));
    act_posClip->setIcon(QIcon(":/PlaneSlice/icons/positive.png"));
    QAction* act_negClip = menu_File->addAction(QString("Reverse"));
    act_negClip->setIcon(QIcon(":/PlaneSlice/icons/negtive.png"));
    QAction* act_centerClip = menu_File->addAction(QString("居中"));
    act_centerClip->setIcon(QIcon(":/PlaneSlice/icons/center.png"));

    QAction* act_testClip = menu_File->addAction(QString("测试"));
    act_testClip->setIcon(QIcon(":/PlaneSlice/icons/how.png"));

    connect(act_ModelOpen, &QAction::triggered, this, [=]()
    {
        QString filePath = QFileDialog::getOpenFileName(this, "open", "C:\\Users\\86187\\Desktop\\testComponents", "STL(*.STL);;");

        // QString sss = "D:/HSP患者数据/stll/tou.stl";
        // QString filePath = sss;;

        if (filePath.isEmpty())
            return;
        else
        {
            //这个变量可以用来修改角色的属性和行为，比如设置它的位置、方向或纹理映射。在VTK的可视化管道中使用actor来表示场景中的对象，并且可以添加到渲染器中以在屏幕上显示它们。
            m_actors = vtkSmartPointer<vtkActor>::New();
            //vtkPolyDataMapper是一个将几何数据转换为图形数据以进行渲染的映射器。vtkSmartPointer是一个模板类，提供VTK对象的自动内存管理
            m_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            // vtkSTLReader是一个读取STL (STereoLithography)文件的阅读器。
            m_STLreader = vtkSmartPointer<vtkSTLReader>::New();

            m_STLreader->SetFileName(filePath.toLocal8Bit().data());
            m_STLreader->Update();    //更新VTK读取器以便读取文件
            m_mapper->SetInputConnection(m_STLreader->GetOutputPort());
            m_actors->SetMapper(m_mapper);
            m_actors->GetProperty()->SetColor(0.6, 0.6, 0.6);
            renderer->AddActor(m_actors);
        }
        renderer->Render();
        renderer->GetActiveCamera()->SetFocalPoint(-100., 10., -20.);
        renderer->GetActiveCamera()->SetPosition(200., 50., 150.);
        renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
        renderer->GetActiveCamera()->SetParallelProjection(1);
        renderer->GetActiveCamera()->SetParallelScale(400);
        renderer->GetActiveCamera()->ComputeViewPlaneNormal();
        renderer->ResetCamera();
    });
    connect(act_Clear, &QAction::triggered, this, [=]()
    {
        pos_num = 0;
        renderer->RemoveActor(m_actors);
        renderer->RemoveActor(point1_actor);
        renderer->RemoveActor(point2_actor);
        renderer->RemoveActor(point3_actor);
        renderer->RemoveActor(plane_actor);
        ui.qvtkWidget->GetRenderWindow()->GetInteractor()->Render();
    });
    connect(act_Settings, &QAction::triggered, this, [=]()
    {
        if (m_IsSlicing == false)
        {
            act_Settings->setIcon(QIcon(":/PlaneSlice/icons/setting.png"));
            m_IsSlicing = !m_IsSlicing;
        }
        else
        {

            act_Settings->setIcon(QIcon(":/PlaneSlice/icons/in_setting.png"));
            m_IsSlicing = !m_IsSlicing;
        }
    });
    connect(act_posClip, &QAction::triggered, this, [=](){fun_posClip();});
    connect(act_negClip, &QAction::triggered, this, [=](){fun_negClip();});
    connect(act_centerClip,&QAction::triggered, this, [=](){setCenter();});

    //测试软件
    connect(act_testClip,&QAction::triggered, this, [=](){cilpmodel();});

    ui.mainToolBar->setStyleSheet("spacing: 5px;");
    ui.mainToolBar->addAction(act_ModelOpen);
    ui.mainToolBar->addAction(act_Clear);
    ui.mainToolBar->addAction(act_Settings);
    ui.mainToolBar->addAction(act_posClip);
    ui.mainToolBar->addAction(act_negClip);
    ui.mainToolBar->addAction(act_centerClip);
    ui.mainToolBar->addAction(act_testClip);

    //该实例用于处理用户与渲染窗口的交互。交互器提供了各种方法来操纵相机、拾取对象和处理鼠标和键盘输入等事件。
    // 一旦创建了交互器，就可以将其附加到 vtkRenderWindow 对象上，使其具备交互功能
    interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor = ui.qvtkWidget->GetRenderWindow()->GetInteractor();
    picker = vtkSmartPointer<vtkCellPicker>::New();  //拾取器，处理用户与渲染窗口的交互，并使用 vtkIdType GetCellId()方法获取所选单元格的 ID
    interactor->SetPicker(picker);


    //将 VTK 中的事件与 Qt 中的槽函数关联起来，使得在事件发生时，Qt 中的槽函数可以被调用。例如，当用户在 VTK 渲染窗口上拖动鼠标时，
    //可以触发 vtkCommand::MouseMoveEvent 事件，并将其与 Qt 中的槽函数关联起来
    vtkQTconnect = vtkSmartPointer<vtkEventQtSlotConnect>::New();
    vtkQTconnect->Connect(ui.qvtkWidget->GetRenderWindow()->GetInteractor(),
                          vtkCommand::LeftButtonPressEvent, this, SLOT(m_mouseClickEvent()));

    //新增
    point1 = vtkSmartPointer<vtkSphereSource>::New();
    point1_actor = vtkSmartPointer<vtkActor>::New();
    point1mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    point1->SetRadius(3);
    point2 = vtkSmartPointer<vtkSphereSource>::New();
    point2_actor = vtkSmartPointer<vtkActor>::New();
    point2mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    point2->SetRadius(3);
    point3 = vtkSmartPointer<vtkSphereSource>::New();
    point3_actor = vtkSmartPointer<vtkActor>::New();
    point3mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    point3->SetRadius(3);


    axesTransformer = vtkSmartPointer<vtkTransform>::New();
    axesTransformer->Translate(0, 0, 0);
    axesActor = vtkSmartPointer<vtkAxesActor>::New();
    axesActor->SetUserTransform(axesTransformer);
    axesActor->SetTotalLength(50, 50, 50);
    axesActor->SetPickable(0);
    axesActor->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(1, 0, 0);  // x颜色
    axesActor->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(0, 1, 0);  // y颜色
    axesActor->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(0, 0, 1);  // z颜色
    axesActor->GetXAxisCaptionActor2D()->GetTextActor()->SetTextScaleModeToNone();  //设置x字体大小
    axesActor->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetFontSize(10);
    axesActor->GetYAxisCaptionActor2D()->GetTextActor()->SetTextScaleModeToNone();  //设置y字体大小
    axesActor->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->SetFontSize(10);
    axesActor->GetZAxisCaptionActor2D()->GetTextActor()->SetTextScaleModeToNone();  //设置z字体大小
    axesActor->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->SetFontSize(10);
    renderer->AddActor(axesActor);
}

PlaneSlice::~PlaneSlice()
{}

void PlaneSlice::m_mouseClickEvent()
{
    if (m_IsSlicing)
    {
        int* clickPos = interactor->GetEventPosition();

        vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
        picker->Pick(clickPos[0], clickPos[1], 0, renderer);

        vtkPoints *pPoints = vtkPoints::New();
        vtkPolyLine *polyLine = vtkPolyLine::New();
        vtkUnstructuredGrid *grid = vtkUnstructuredGrid::New();
        vtkDataSetMapper *mapper = vtkDataSetMapper::New();
        vtkActor *actor = vtkActor::New();

        if (picker->GetActor() != NULL)
        {
            int x = pos_num * 3 + 0;
            int y = pos_num * 3 + 1;
            int z = pos_num * 3 + 2;
            double* pos = picker->GetPickPosition();
            plane_pos[x] = pos[0];
            plane_pos[y] = pos[1];
            plane_pos[z] = pos[2];
            switch (pos_num)
            {
            case 0:
                point1->SetCenter(pos[0], pos[1], pos[2]);
                point1mapper->SetInputConnection(point1->GetOutputPort());
                point1_actor->SetMapper(point1mapper);
                point1_actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // 设置颜色为红色
                renderer->AddActor(point1_actor);
                break;
            case 1:
                point2->SetCenter(pos[0], pos[1], pos[2]);
                point2mapper->SetInputConnection(point2->GetOutputPort());
                point2_actor->SetMapper(point2mapper);
                point2_actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // 设置颜色为红色
                renderer->AddActor(point2_actor);
                break;
            case 2:
                point3->SetCenter(pos[0], pos[1], pos[2]);
                point3mapper->SetInputConnection(point3->GetOutputPort());
                point3_actor->SetMapper(point3mapper);
                point3_actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // 设置颜色为红色
                renderer->AddActor(point3_actor);
                break;
            default:
                break;
            }
        }

        if (pos_num == 2)
        {
            vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
            points->InsertNextPoint(plane_pos[0], plane_pos[1], plane_pos[2]);
            points->InsertNextPoint(plane_pos[3], plane_pos[4], plane_pos[5]);
            points->InsertNextPoint(plane_pos[6], plane_pos[7], plane_pos[8]);

            planeSource = vtkSmartPointer<vtkPlaneSource>::New();
            planeSource->SetOrigin(points->GetPoint(0));
            planeSource->SetPoint1(points->GetPoint(1));
            planeSource->SetPoint2(points->GetPoint(2));

            plane = vtkSmartPointer<vtkPlane>::New();
            plane->SetNormal(planeSource->GetNormal());
            plane->SetOrigin(planeSource->GetOrigin());

            plane_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            plane_actor = vtkSmartPointer<vtkActor>::New();
            plane_mapper->SetInputConnection(planeSource->GetOutputPort());
            plane_actor->SetMapper(plane_mapper);
            plane_actor->GetProperty()->SetColor(0.75,0.65,0.65);
            plane_actor->GetProperty()->SetOpacity(0.8);

            //renderer->AddActor(plane_actor);
            pos_num = 0;

            vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
            cutter->SetCutFunction(plane);
            cutter->SetInputData(m_STLreader->GetOutput());  // 不走内存的方式
            cutter->SetSortByToSortByValue();
            vtkSmartPointer<vtkPolyDataMapper> cutterMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            cutterMapper->SetInputConnection(cutter->GetOutputPort());
            cutterMapper->ScalarVisibilityOn();
            plane_actor->GetProperty()->SetColor(0.4, 0.8, 0.2);
            plane_actor->GetProperty()->SetLineWidth(5);
            plane_actor->SetMapper(cutterMapper);
            renderer->AddActor(plane_actor);
            // 获取线条
            //vtkSmartPointer<vtkStripper> stripper = vtkSmartPointer<vtkStripper>::New();
            //stripper->SetInputConnection(cutter->GetOutputPort()); // valid circle
            //stripper->JoinContiguousSegmentsOn();
            //stripper->Update();
            //vtkSmartPointer<vtkActor> imageActor3 = vtkSmartPointer<vtkActor>::New();
            //vtkSmartPointer<vtkPolyDataMapper> tempMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            //tempMapper->SetInputData(stripper->GetOutput());
            //imageActor3->SetMapper(tempMapper);
            //imageActor3->GetProperty()->SetColor(1, 0, 0);
            //renderer->AddActor(imageActor3);

            polyLine->GetPointIds()->SetNumberOfIds(points->GetNumberOfPoints());
            for(int i = 0; i < points->GetNumberOfPoints(); i++)
            {
                polyLine->GetPointIds()->SetId(i, i);
            }

            grid->Allocate(1, 1);
            grid->InsertNextCell(polyLine->GetCellType(), polyLine->GetPointIds());
            grid->SetPoints(points);
            mapper->SetInputData(grid);
            actor->SetMapper(mapper);
            actor->GetProperty()->SetColor(1.0, 0.0, 0.0); //设置颜色


            m_isClipOk = true;

            interactor->Render();
        }
        else
        {
            m_isClipOk = false;
            pos_num++;
            m_mapper->SetInputConnection(m_STLreader->GetOutputPort());
            renderer->RemoveActor(plane_actor);
            interactor->Render();
        }

    }
}

void PlaneSlice::fun_posClip()
{
    if (m_isClipOk == true)
    {
        //可以将 vtkPolyData 对象沿着一个平面进行裁剪，保留裁剪平面一侧的几何形状，去除另一侧的几何形状，从而实现裁剪功能
        //裁剪操作会改变原始的 vtkPolyData 对象，因此需要进行备份或使用副本
        vtkSmartPointer<vtkClipPolyData> clipper = vtkSmartPointer<vtkClipPolyData>::New();
        clipper->SetInputConnection(m_STLreader->GetOutputPort());
        clipper->SetClipFunction(plane);
        clipper->InsideOutOn();
        clipper->Update();

        m_mapper->SetInputConnection(clipper->GetOutputPort());
        interactor->Render();
    }
}

void PlaneSlice::fun_negClip()
{
    if (m_isClipOk == true)
    {
        vtkSmartPointer<vtkClipPolyData> clipper =
                vtkSmartPointer<vtkClipPolyData>::New();
        clipper->SetInputConnection(m_STLreader->GetOutputPort());
        clipper->SetClipFunction(plane);
        clipper->InsideOutOff();
        clipper->Update();

        m_mapper->SetInputConnection(clipper->GetOutputPort());
        interactor->Render();
    }
}

void PlaneSlice::setCenter()
{

    vtkPolyData* polydata = m_STLreader->GetOutput();

    if(polydata != nullptr)
    {
        double bounds[6];
        polydata->GetBounds(bounds);

        double center[3];
        polydata->GetCenter(center);

        double minX = bounds[0];
        double maxX = bounds[1];
        double minY = bounds[2];
        double maxY = bounds[3];
        double minZ = bounds[4];
        double maxZ = bounds[5];

        qDebug()<<"minX<<<<<"<<minX;
        qDebug()<<"maxX<<<<"<<maxX;
        qDebug()<<"minY<<<<<"<<minY;
        qDebug()<<"maxY<<<<"<<maxY;
        qDebug()<<"minZ<<<<<"<<minZ;
        qDebug()<<"maxZ<<<<"<<maxZ;

        qDebug()<<"center<<<"<<center[0]<<center[1]<<center[2];

        // 创建一个平移变换对象
        vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
        transform->Translate(100.0, 0.0, 0.0); // 在 x 轴正方向上平移 1.0 个单位
        // 将变换应用到模型的 vtkActor 对象上
        m_actors->SetUserTransform(transform);

        ui.qvtkWidget->GetRenderWindow()->Render();
        interactor->Start();

        double center1[3];
        polydata->GetCenter(center1);
        qDebug()<<"center1<<<"<<center1[0];
    }
}

void PlaneSlice::cilpmodel()
{
    QString sss = "D:/HSP患者数据/stll/tou.stl";
    QString filePath = sss;;

    m_STLreader = vtkSmartPointer<vtkSTLReader>::New();

    m_STLreader->SetFileName(filePath.toLocal8Bit().data());
    m_STLreader->Update();    //更新VTK读取器以便读取文件

    vtkSmartPointer<vtkGPUVolumeRayCastMapper> origMapper =
            vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    origMapper->SetInputData(m_STLreader->GetOutput());

    vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper =
            vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    volumeMapper->SetInputData(m_STLreader->GetOutput());

    vtkSmartPointer<vtkPlane> plane =
            vtkSmartPointer<vtkPlane>::New();
    plane->SetOrigin(120, 120, 0);
    plane->SetNormal(1, 1, 0);
    volumeMapper->AddClippingPlane(plane);

    /*****************************************************************/
    //设置体绘制相关属性
    vtkSmartPointer<vtkVolumeProperty> volumeProperty =
            vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->SetInterpolationTypeToLinear(); //设置线性插值方式
    volumeProperty->ShadeOn();//开启阴影属性
    volumeProperty->SetAmbient(0.4);//设置环境温度
    volumeProperty->SetDiffuse(0.6);//设置漫反射系数
    volumeProperty->SetSpecular(0.2);//设置镜面反射系数
    //添加灰度不透明度属性
    vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
            vtkSmartPointer<vtkPiecewiseFunction>::New();
    compositeOpacity->AddPoint(70, 0.0);
    compositeOpacity->AddPoint(90, 0.4);
    compositeOpacity->AddPoint(180, 0.6);
    volumeProperty->SetScalarOpacity(compositeOpacity);
    //添加梯度不同明度属性
    vtkSmartPointer<vtkPiecewiseFunction> gradientOpacity =
            vtkSmartPointer<vtkPiecewiseFunction>::New();
    gradientOpacity->AddPoint(10, 0.0);
    gradientOpacity->AddPoint(90, 0.5);
    gradientOpacity->AddPoint(100, 1.0);
    volumeProperty->SetGradientOpacity(gradientOpacity);
    //添加颜色传输
    vtkSmartPointer<vtkColorTransferFunction> color =
            vtkSmartPointer<vtkColorTransferFunction>::New();
    color->AddRGBPoint(0, 0, 0, 0);
    color->AddRGBPoint(64, 1.0, 0.52, 0.3);
    color->AddRGBPoint(190.0, 1.00, 1.00, 1.00);
    color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);
    volumeProperty->SetColor(color);
    /***********************************************************/
    //渲染管道
    vtkSmartPointer<vtkVolume> origVolume =
            vtkSmartPointer<vtkVolume>::New();
    origVolume->SetMapper(origMapper);
    origVolume->SetProperty(volumeProperty);

    vtkSmartPointer<vtkVolume> clippingVolume =
            vtkSmartPointer<vtkVolume>::New();
    clippingVolume->SetMapper(volumeMapper);
    clippingVolume->SetProperty(volumeProperty);


    double origView[4] = { 0, 0, 0.5, 1 };
    double croppingView[4] = { 0.5, 0, 1, 1 };


    vtkSmartPointer<vtkRenderer> origRender =
            vtkSmartPointer<vtkRenderer>::New();
    origRender->AddVolume(origVolume);
    origRender->SetBackground(1, 1, 0);
    origRender->SetViewport(origView);

    ui.qvtkWidget->GetRenderWindow()->AddRenderer(origRender);

    vtkSmartPointer<vtkRenderer> clippingRender =
            vtkSmartPointer<vtkRenderer>::New();
    clippingRender->AddVolume(clippingVolume);
    clippingRender->SetBackground(0, 1, 0);
    clippingRender->SetViewport(croppingView);


    vtkSmartPointer<vtkRenderWindowInteractor> rwi =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();

    rwi = ui.qvtkWidget->GetRenderWindow()->GetInteractor();

    origRender->GetActiveCamera()->SetPosition(0, -1, 0);
    origRender->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    origRender->GetActiveCamera()->SetViewUp(0, 0, 1);
    origRender->GetActiveCamera()->Azimuth(30);
    origRender->GetActiveCamera()->Elevation(30);
    origRender->ResetCamera();
    clippingRender->SetActiveCamera(origRender->GetActiveCamera());

    ui.qvtkWidget->GetRenderWindow()->Render();
    rwi->Start();

}

void PlaneSlice::cilp2()
{
    //    vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    //    reader->SetFileName("E:\\TestData\\cow.vtp");

    //    vtkSmartPointer<vtkPolyDataNormals> cow_normals = vtkSmartPointer<vtkPolyDataNormals>::New();
    //    cow_normals->SetInputConnection(reader->GetOutputPort());

    //    vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
    //    plane->SetOrigin(0.25, 0.0, 0.0);
    //    plane->SetNormal(-1, -1, 0);

    //    vtkSmartPointer<vtkClipPolyData> clipper = vtkSmartPointer<vtkClipPolyData>::New();
    //    clipper->SetInputConnection(cow_normals->GetOutputPort());
    //    clipper->SetClipFunction(plane);
    //    clipper->GenerateClipScalarsOn();
    //    clipper->GenerateClippedOutputOn();
    //    clipper->SetValue(0.5);

    //    vtkSmartPointer<vtkPolyDataMapper> clip_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //    clip_mapper->SetInputConnection(clipper->GetOutputPort());
    //    clip_mapper->ScalarVisibilityOff();

    //    vtkSmartPointer<vtkProperty> backProp = vtkSmartPointer<vtkProperty>::New();
    //    backProp->SetDiffuseColor(1.00, 0.388, 0.278);

    //    vtkSmartPointer<vtkActor> clip_actor = vtkSmartPointer<vtkActor>::New();
    //    clip_actor->SetMapper(clip_mapper);
    //    clip_actor->GetProperty()->SetColor(.200, .631, .788);
    //    clip_actor->SetBackfaceProperty(backProp);


    //    vtkSmartPointer<vtkPolyDataMapper> rest_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //    rest_mapper->SetInputConnection(clipper->GetClippedOutputPort());
    //    rest_mapper->ScalarVisibilityOff();

    //    vtkSmartPointer<vtkActor> rest_actor = vtkSmartPointer<vtkActor>::New();
    //    rest_actor->SetMapper(rest_mapper);
    //    rest_actor->GetProperty()->SetRepresentationToWireframe();


    //    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //    renderer->AddActor(clip_actor);
    //    renderer->AddActor(rest_actor);
    //    renderer->SetBackground(1.0, 1.0, 1.0);


    //    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    //    renWin->AddRenderer(renderer);
    //    renWin->SetSize(640, 480);
    //    renWin->Render();
    //    renWin->SetWindowName("ClipExample");

    //    vtkSmartPointer<vtkRenderWindowInteractor> iren =
    //            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //    iren->SetRenderWindow(renWin);

    //    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    //            vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    //    iren->SetInteractorStyle(style);

    //    iren->Initialize();
    //    iren->Start();

}
