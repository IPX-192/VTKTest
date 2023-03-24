//#ifndef MOUSEINTERACTORSTYLE_H
//#define MOUSEINTERACTORSTYLE_H

//#include <vtkSmartPointer.h>
//#include <vtkPolyData.h>
//#include <vtkPoints.h>
//#include <vtkCellArray.h>
//#include <vtkPolyDataMapper.h>
//#include <vtkActor.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>
//#include <vtkInteractorStyleTrackballActor.h>
//#include <vtkPointPicker.h>
//#include <vtkProperty.h>
//#include <vtkLineSource.h>
//#include <vtkSphereSource.h>
//#include <vtkCommand.h>

//class MouseInteractorStyle : public vtkInteractorStyleTrackballActor {
//public:
//    static MouseInteractorStyle* New();
//    vtkTypeMacro(MouseInteractorStyle, vtkInteractorStyleTrackballActor);

//    MouseInteractorStyle() {
//        drawing = false;
//        pointList = vtkSmartPointer<vtkPoints>::New();
//        pointListPolyData = vtkSmartPointer<vtkPolyData>::New();
//        pointListPolyData->SetPoints(pointList);
//        pointListMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//        pointListMapper->SetInputData(pointListPolyData);
//        pointListActor = vtkSmartPointer<vtkActor>::New();
//        pointListActor->SetMapper(pointListMapper);
//        pointListActor->GetProperty()->SetColor(0, 0, 1);
//        this->line = vtkSmartPointer<vtkLineSource>::New();
//        this->lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//        this->lineMapper->SetInputConnection(this->line->GetOutputPort());
//        this->lineActor = vtkSmartPointer<vtkActor>::New();
//        this->lineActor->SetMapper(this->lineMapper);
//        this->lineActor->GetProperty()->SetColor(0, 1, 0);
//        this->point = vtkSmartPointer<vtkSphereSource>::New();
//        this->point->SetRadius(0.1);
//        this->pointMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//        this->pointMapper->SetInputConnection(this->point->GetOutputPort());
//        this->pointActor = vtkSmartPointer<vtkActor>::New();
//        this->pointActor->SetMapper(this->pointMapper);
//        this->pointActor->GetProperty()->SetColor(1, 0, 0);
//        this->drawing = false;
//    }

//    ~MouseInteractorStyle() {}

//    void OnLeftButtonDown() {
//        this->drawing = true;
//        int* pos = this->GetInteractor()->GetEventPosition();
//        vtkSmartPointer<vtkPointPicker> picker = vtkSmartPointer<vtkPointPicker>::New();
//        picker->Pick(pos[0], pos[1], 0, this->CurrentRenderer);
//        this->pointList->InsertNextPoint(picker->GetPickPosition());
//        this->pointListPolyData->Modified();
//    }

//    void OnLeftButtonUp() {
//        this->drawing = false;
//    }

//    void OnMouseMove() {
//        if (drawing) {
//            int* pos = this->GetInteractor()->GetEventPosition();
//            vtkSmartPointer<vtkPointPicker> picker = vtkSmartPointer<vtkPointPicker>::New();
//            picker->Pick(pos[0], pos[1], 0, this->CurrentRenderer);
//            int lastPointIndex = this->pointList->GetNumberOfPoints()-1;
//            this->line->SetPoint1(lastPointIndex, picker->GetPickPosition());
//            this->pointList->SetPoint(lastPointIndex, picker->GetPickPosition());
//            this->line->Modified();
//            this->pointListPolyData->Modified();
//        }
//    }

//private:
//    bool drawing;
//    vtkSmartPointer<vtkPoints> pointList;
//    vtkSmartPointer<vtkPolyData> pointListPolyData;
//    vtkSmartPointer<vtkPolyDataMapper> pointListMapper;
//    vtkSmartPointer<vtkActor> pointListActor;
//    vtkSmartPointer<vtkLineSource> line;
//    vtkSmartPointer<vtkPolyDataMapper> lineMapper;
//    vtkSmartPointer<vtkActor> lineActor;
//    vtkSmartPointer<vtkSphereSource> point;
//    vtkSmartPointer<vtkPolyDataMapper> pointMapper;
//    vtkSmartPointer<vtkActor> pointActor;
//};



//#endif // MOUSEINTERACTORSTYLE_H
