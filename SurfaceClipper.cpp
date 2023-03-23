//#include "Surfaceclipper.h"
//#include <QDebug>
//#include <vtkPoints.h>
//#include <vtkCamera.h>
//#include <vtkCutter.h>
//#include <vtkPlanes.h>
//#include <vtkSphere.h>

//#include <vtkStripper.h>
//#include <vtkProperty.h>
//#include <vtkPointData.h>
//#include <vtkProperty2D.h>
//#include <vtkClipPolyData.h>
//#include <vtkContourFilter.h>
//#include <vtkCleanPolyData.h>
//#include <vtkPolyDataMapper.h>
//#include <vtkBoxClipDataSet.h>
//#include <vtkSeedRepresentation.h>
//#include <vtkDataSetSurfaceFilter.h>
//#include <vtkPolyDataConnectivityFilter.h>
//#include <vtkPointHandleRepresentation2D.h>


//SurfaceClipper::SurfaceClipper(QObject *parent) : QObject(parent) {
//    Initial();
//}

//SurfaceClipper::~SurfaceClipper() {
//    if (own_renderer_) {
//        vmtk_renderer_->deleteLater();
//    }
//}

///**
// * @brief SurfaceClipper::Execute
// * ui交互开启
// */
//void SurfaceClipper::Execute() {
//    qDebug();
//    if (surface_ == nullptr) {
//        qWarning() << "no Surface";
//        return ;
//    }
//    if (vmtk_renderer_ == nullptr) {
//        vmtk_renderer_ = new vtkRenderer();
//        vmtk_renderer_->Initialize();
//        own_renderer_ = true;
//    }

//    //初始化
//    if (widget_type_ == BOX) {
//        if (clip_box_widget_ == nullptr) {
//            clip_box_widget_ = vtkSmartPointer<vtkBoxWidget>::New();
//            clip_box_widget_->GetFaceProperty()->SetColor(0.6, 0.6, 0.2);
//            clip_box_widget_->GetFaceProperty()->SetOpacity(0.25);
//            clip_box_widget_->SetInteractor(
//                        vmtk_renderer_->GetRenderWindowInteractor());
//        }
//    } else if (widget_type_ == SPHERE) {
//        if (clip_sphere_widget_ == nullptr) {
//            clip_sphere_widget_ = vtkSmartPointer<vtkSphereWidget>::New();
//            clip_sphere_widget_->GetSphereProperty()->SetColor(0.6, 0.6, 0.2);
//            clip_sphere_widget_->GetSphereProperty()->SetOpacity(0.25);
//            clip_sphere_widget_->GetSelectedSphereProperty()
//                    ->SetColor(0.6, 0.0, 0.0);
//            clip_sphere_widget_->GetSelectedSphereProperty()
//                    ->SetOpacity(0.75);
//            clip_sphere_widget_->SetRepresentationToSurface();
//            clip_sphere_widget_->SetPhiResolution(20);
//            clip_sphere_widget_->SetThetaResolution(20);
//            clip_sphere_widget_->SetInteractor(
//                        vmtk_renderer_->GetRenderWindowInteractor());
//        }
//    } else if (widget_type_ == LINE) {
//        if (this->seed_widget_ == nullptr) {
//            this->seed_widget_ = vtkSmartPointer<vtkSeedWidget>::New();
//            vtkNew<vtkPointHandleRepresentation2D> handle_rep;
//            handle_rep->GetProperty()->SetColor(1, 0, 0);
//            vtkNew<vtkSeedRepresentation> widget_rep;
//            widget_rep->SetHandleRepresentation(handle_rep);
//            this->seed_widget_->SetInteractor(
//                        this->vmtk_renderer_->GetRenderWindowInteractor());
//            this->seed_widget_->SetRepresentation(widget_rep);
//        }
//        qint32 num_seeds =
//                this->seed_widget_->GetSeedRepresentation()->GetNumberOfSeeds();
//        for (qint32 i = 0; i < num_seeds; ++i) {
//            this->seed_widget_->GetSeedRepresentation()->RemoveLastHandle();
//            this->seed_widget_->DeleteSeed(
//                        this->seed_widget_->GetSeedRepresentation()->GetNumberOfSeeds());
//        }
//    }
//    if (first_connect_) {
//        connect(vmtk_renderer_, &vtkRenderer::SignalKeyPressed,
//                this, &SurfaceClipper::SlotKeyPressed);
//        this->vtk_connections_ = vtkSmartPointer<vtkEventQtSlotConnect>::New();
//        vtk_connections_->Connect(seed_widget_, vtkCommand::PlacePointEvent,
//                                  this, SLOT(SlotSeedChanged(vtkObject *, unsigned long,
//                                                             void *, void *)));
//        first_connect_ = false;
//    }
//    transform_ = vtkSmartPointer<vtkTransform>::New();
//    if (widget_type_ == BOX) {
//        clip_box_widget_->GetTransform(transform_);
//    }
//    Display();
//    if (own_renderer_) {
//        vmtk_renderer_->Deallocate();
//    }
//}

///**
// * @brief SurfaceClipper::SetSurface
// * 设置输入模型
// * @param value
// */
//void SurfaceClipper::SetSurface(const vtkSmartPointer<vtkPolyData> value) {
//    surface_ = value;
//}

///**
// * @brief SurfaceClipper::SetWidgetType
// * 设置切割方式
// * @param value
// */
//void SurfaceClipper::SetWidgetType(const SurfaceClipper::WidgetType value) {
//    widget_type_ = value;
//}

///**
// * @brief SurfaceClipper::SetTransform
// * 设置Trans转换
// * @param value
// */
//void SurfaceClipper::SetTransform(const vtkSmartPointer<vtkTransform> value) {
//    transform_ = value;
//}

///**
// * @brief SurfaceClipper::SetInsideOut
// * 设置是否取反
// * @param value
// */
//void SurfaceClipper::SetInsideOut(const bool value) {
//    inside_out_ = value;
//}

///**
// * @brief SurfaceClipper::SetvtkRenderer
// * 输入Renderer
// * @param value
// */
//void SurfaceClipper::SetvtkRenderer(const QPointer<vtkRenderer> value) {
//    vmtk_renderer_ = value;
//}

///**
// * @brief SurfaceClipper::GetSurface
// * 获取剪切后模型（交）
// * @return
// */
//vtkSmartPointer<vtkPolyData> SurfaceClipper::GetSurface() const {
//    return surface_;
//}

///**
// * @brief SurfaceClipper::GetClippedSurface
// * 获取剪切后模型（异）
// * @return
// */
//vtkSmartPointer<vtkPolyData> SurfaceClipper::GetClippedSurface() const {
//    return clipped_surface_;
//}

///**
// * @brief SurfaceClipper::GetCutLines
// * 获取剪切后交线
// * @return
// */
//vtkSmartPointer<vtkPolyData> SurfaceClipper::GetCutLines() const {
//    return cut_lines_;
//}

///**
// * @brief SurfaceClipper::GetTransForm
// * BOX模式剪切转换
// * @return
// */
//vtkSmartPointer<vtkTransform> SurfaceClipper::GetTransForm() const {
//    return transform_;
//}

///**
// * @brief SurfaceClipper::Initial
// * 初始化
// */
//void SurfaceClipper::Initial() {
//    surface_ = nullptr;
//    clipped_surface_ = nullptr;
//    cut_lines_ = nullptr;
//    vmtk_renderer_ = nullptr;
//    clip_box_widget_ = nullptr;
//    clip_sphere_widget_ = nullptr;
//    first_connect_ = true;
//    own_renderer_ = false;
//    transform_ = nullptr;
//    widget_type_ = LINE;
//    inside_out_ = true;
//    setObjectName("vmtksurfaceclipper");
//}

///**
// * @brief SurfaceClipper::Display
// * 开启widget
// */
//void SurfaceClipper::Display() {
//    if (widget_type_ == BOX) {
//        clip_box_widget_->SetInputData(surface_);
//        clip_box_widget_->PlaceWidget();
//    } else if (widget_type_ == SPHERE) {
//        clip_sphere_widget_->SetInputData(surface_);
//        clip_sphere_widget_->PlaceWidget();
//        clip_sphere_widget_->On();
//    } else if (widget_type_ == LINE) {
//        this->seed_widget_->On();
//    }
//    if (transform_ && widget_type_ == BOX) {
//        clip_box_widget_->SetTransform(transform_);
//        clip_box_widget_->On();
//    }
//    vmtk_renderer_->Render();
//}

///**
// * @brief SurfaceClipper::ClipCallback
// * 剪裁函数
// */
//void SurfaceClipper::ClipCallback() {
//    qDebug();
//    if ((widget_type_ == BOX &&
//         clip_box_widget_->GetEnabled() != 1) ||
//            (widget_type_ == SPHERE &&
//             clip_sphere_widget_->GetEnabled() != 1)) {
//        return ;
//    }
//    if(widget_type_ == LINE) {
//        if (this->seed_widget_->GetSeedRepresentation()->GetNumberOfSeeds() != 2
//                || this->surface_ == nullptr) {
//            return ;
//        }
//        double pos1[3], pos2[3];
//        this->seed_widget_->GetSeedRepresentation()->GetSeedWorldPosition(0, pos1);
//        this->seed_widget_->GetSeedRepresentation()->GetSeedWorldPosition(1, pos2);
//        this->seed_widget_->Off();
//        QList<QList<double>> pts = {
//            {0, 0, 0},
//            {1, 0, 0},
//            {1, 1, 0},
//            {0, 1, 0},
//            {0, 0, 1},
//            {1, 0, 1},
//            {1, 1, 1},
//            {0, 1, 1}
//        };
//        vtkNew<vtkPoints> points;
//        for (qint32 i = 0; i < pts.size(); ++i) {
//            points->InsertPoint(i, pts[i][0], pts[i][1], pts[i][2]);
//        }
//        double direction[3];
//        this->vmtk_renderer_->GetRenderer()->GetActiveCamera()
//                ->GetDirectionOfProjection(direction);
//        points->SetPoint(0,
//                         pos1[0] - direction[0] * 1000,
//                pos1[1] - direction[1] * 1000,
//                pos1[2] - direction[2] * 1000);
//        points->SetPoint(3,
//                         pos1[0] + direction[0] * 1000,
//                pos1[1] + direction[1] * 1000,
//                pos1[2] + direction[2] * 1000);
//        points->SetPoint(1,
//                         pos2[0] - direction[0] * 1000,
//                pos2[1] - direction[1] * 1000,
//                pos2[2] - direction[2] * 1000);
//        points->SetPoint(2,
//                         pos2[0] + direction[0] * 1000,
//                pos2[1] + direction[1] * 1000,
//                pos2[2] + direction[2] * 1000);
//        double direction2[3], direction_offset[3];
//        direction2[0] = pos1[0] - pos2[0];
//        direction2[1] = pos1[1] - pos2[1];
//        direction2[2] = pos1[2] - pos2[2];
//        vtkMath::Cross(direction, direction2, direction_offset);
//        points->SetPoint(4,
//                         pos1[0] - direction[0] * 1000 + direction_offset[0] * 0.01,
//                pos1[1] - direction[1] * 1000 + direction_offset[1] * 0.01,
//                pos1[2] - direction[2] * 1000 + direction_offset[2] * 0.01);
//        points->SetPoint(7,
//                         pos1[0] + direction[0] * 1000 + direction_offset[0] * 0.01,
//                pos1[1] + direction[1] * 1000 + direction_offset[1] * 0.01,
//                pos1[2] + direction[2] * 1000 + direction_offset[2] * 0.01);
//        points->SetPoint(5,
//                         pos2[0] - direction[0] * 1000 + direction_offset[0] * 0.01,
//                pos2[1] - direction[1] * 1000 + direction_offset[1] * 0.01,
//                pos2[2] - direction[2] * 1000 + direction_offset[2] * 0.01);
//        points->SetPoint(6,
//                         pos2[0] + direction[0] * 1000 + direction_offset[0] * 0.01,
//                pos2[1] + direction[1] * 1000 + direction_offset[1] * 0.01,
//                pos2[2] + direction[2] * 1000 + direction_offset[2] * 0.01);
//        vtkNew<vtkBoxClipDataSet> box_clip;
//        box_clip->SetInputData(this->surface_);
//        box_clip->GenerateClippedOutputOn();
//        double n0[3], n1[3], n2[3], n3[3], n4[3], n5[3];
//        double p0[3], p1[3], p2[3], p3[3], p4[3], p5[3];
//        double pt0[3], pt1[3], pt2[3], pt3[3], pt4[3], pt5[3], pt6[3], pt7[3];
//        points->GetPoint(0, pt0);
//        points->GetPoint(1, pt1);
//        points->GetPoint(2, pt2);
//        points->GetPoint(3, pt3);
//        points->GetPoint(4, pt4);
//        points->GetPoint(5, pt5);
//        points->GetPoint(6, pt6);
//        points->GetPoint(7, pt7);
//        for (qint32 i = 0; i < 3; ++i) {
//            p0[i] = (pt1[i] + pt3[i]) / 2;
//            n0[i] = (pt1[i] - pt5[i]);
//            p1[i] = (pt5[i] + pt7[i]) / 2;
//            n1[i] = (pt5[i] - pt1[i]);
//            p2[i] = (pt2[i] + pt5[i]) / 2;
//            n2[i] = (pt5[i] - pt4[i]);
//            p3[i] = (pt3[i] + pt4[i]) / 2;
//            n3[i] = (pt4[i] - pt5[i]);
//            p4[i] = (pt0[i] + pt5[i]) / 2;
//            n4[i] = (pt5[i] - pt6[i]);
//            p5[i] = (pt2[i] + pt7[i]) / 2;
//            n5[i] = (pt6[i] - pt5[i]);
//        }
//        box_clip->SetBoxClip(n0, p0,
//                             n1, p1,
//                             n2, p2,
//                             n3, p3,
//                             n4, p4,
//                             n5, p5);
//        vtkNew<vtkDataSetSurfaceFilter> surface_in;
//        surface_in->SetInputConnection(box_clip->GetOutputPort(0));
//        vtkNew<vtkDataSetSurfaceFilter> surface_out;
//        surface_out->SetInputConnection(box_clip->GetOutputPort(1));
//        vtkNew<vtkPolyDataConnectivityFilter> connectivity_filter;
//        connectivity_filter->SetInputConnection(surface_out->GetOutputPort());
//        connectivity_filter->SetExtractionModeToLargestRegion();
//        connectivity_filter->Update();
//        this->surface_ = connectivity_filter->GetOutput();
//        return;
//    }
//    vtkSmartPointer<vtkClipPolyData> clipper = vtkSmartPointer<vtkClipPolyData>::New();
//    vtkSmartPointer<vtkPlanes> clip_planes_function;
//    vtkSmartPointer<vtkSphere> clip_sphere_function;
//    clipper->SetInputData(surface_);
//    clipper->GenerateClippedOutputOn();
//    clipper->SetInsideOut(inside_out_);
//    if (widget_type_ == BOX) {
//        clip_planes_function = vtkSmartPointer<vtkPlanes>::New();
//        clipper->SetClipFunction(clip_planes_function);
//    } else if (widget_type_ == SPHERE) {
//        clip_sphere_function = vtkSmartPointer<vtkSphere>::New();
//        clipper->SetClipFunction(clip_sphere_function);
//    }
//    vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
//    cutter->SetInputData(surface_);
//    if (widget_type_ == BOX) {
//        cutter->SetCutFunction(clip_planes_function);
//    } else if (widget_type_ == SPHERE) {
//        cutter->SetCutFunction(clip_sphere_function);
//    }
//    clipped_surface_ = vtkSmartPointer<vtkPolyData>::New();
//    cut_lines_ = vtkSmartPointer<vtkPolyData>::New();
//    if (widget_type_ == BOX) {
//        clip_box_widget_->GetPlanes(clip_planes_function);
//    } else if (widget_type_ == SPHERE) {
//        clip_sphere_widget_->GetSphere(clip_sphere_function);
//    }
//    clipper->Update();
//    if (widget_type_ == BOX) {
//        clip_box_widget_->Off();
//    } else if (widget_type_ == SPHERE) {
//        clip_sphere_widget_->Off();
//    }
//    cutter->Update();
//    cut_lines_->DeepCopy(cutter->GetOutput());
//    surface_->DeepCopy(clipper->GetOutput());
//    clipped_surface_->DeepCopy(clipper->GetClippedOutput());
//}

///**
// * @brief SurfaceClipper::SlotKeyPressed
// * 键盘回调函数
// * @param key
// */
//void SurfaceClipper::SlotKeyPressed(const QString &key) {
//    if (key == "space") {
//        ClipCallback();
//        emit SignalClippedFinish();
//    } else if (key == "Escape") {
//        if (widget_type_ == BOX) {
//            clip_box_widget_->Off();
//        } else if (widget_type_ == SPHERE) {
//            clip_sphere_widget_->Off();
//        } else if (widget_type_ == SPHERE) {
//            seed_widget_->Off();
//        }
//        emit SignalClippedFinish();
//    }
//}

///**
// * @brief SurfaceClipper::SetEnable
// * 设置是否启动
// * @param value
// */
//void SurfaceClipper::SetEnable(const bool value) {
//    if (widget_type_ == BOX) {
//        clip_box_widget_->SetEnabled(value);
//    } else if (widget_type_ == SPHERE) {
//        clip_sphere_widget_->SetEnabled(value);
//    }
//}

///**
// * @brief SurfaceClipper::SlotSeedChanged
// * 点选取后槽函数
// * @param caller
// * @param vtk_event
// * @param client_data
// * @param call_data
// */
//void SurfaceClipper::SlotSeedChanged(
//        vtkObject *caller, unsigned long vtk_event,
//        void *client_data, void *call_data) {
//    Q_UNUSED(client_data)
//    if (vtk_event == vtkCommand::PlacePointEvent) {
//        qint32 n = *static_cast<int *>(call_data);
//        vtkSmartPointer<vtkSeedWidget> widget = dynamic_cast<vtkSeedWidget *>(caller);
//        if (n >= 0 && widget) {
//            qint32 num_seeds = widget->GetSeedRepresentation()->GetNumberOfSeeds();
//            if (num_seeds > 2) {
//                this->seed_widget_->DeleteSeed(0);
//            }
//        }
//    }
//}

