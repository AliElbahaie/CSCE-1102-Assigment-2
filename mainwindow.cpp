#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    searchTime = 0;
    sortTime = 0;
    ui->info->setText("Dataset size: " + QString::number(size) + "\n\nSorting Type: " + SortingType + "\n\nSearch Type: " + SearchType);
}

MainWindow::~MainWindow()
{
    delete [] arr;
    delete ui;
}

void MainWindow::NormalSearch(int num)
{
    if(exists)
    {
        for(int i=0;i<size;i++)
        {
            if(arr[i]==num)
            {
                if(!found)
                {
                    found = true;
                    ui->status->setText("FOUND\n" + QString::number(num) + " is in index number:" + QString::number(i));
                }
                else
                {
                    ui->status->setText(ui->status->text() + ", " + QString::number(i));
                }
            }
        }
        if(!found && ui->number->text()!="")
        {
            ui->status->setText("number: " + QString::number(num) + " was not found!");
            found = false;
        }
        else if(!found)
        {
            ui->status->setText("please type a number");
            found = false;
        }
        found = false;
    }
}

int MainWindow::BinarySearch(int array[], int num, int low, int high)
{
      while (low <= high) {
        int mid = low + (high - low) / 2;

        if (array[mid] == num)
        {
            ui->status->setText("FOUND\n" + QString::number(num) + " is in index number: " + QString::number(mid));
            return mid;
        }

        if (array[mid] < num)
        {low = mid + 1;}

        else
        {high = mid - 1;}
      }
      ui->status->setText("number: " + QString::number(num) + " was not found!");

      return -1;

}


void MainWindow::mergesort(int array[],int start,int end)
{
  int mid;
  if(start < end)
  {
     mid = (start + end) /2;
     mergesort(array,start,mid);
     mergesort(array,mid+1,end);
     merge(array,start,mid,end);
   }
}

void MainWindow::merge(int arr[],int start,int mid,int end)
{
    int i = start;
      int j = mid + 1;
      int k = start;

      int temp[size];

      while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
          temp[k] = arr[i];
          i++;
          k++;
        } else {
          temp[k] = arr[j];
          j++;
          k++;
        }
      }
      while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
      }
      while (j <= end) {
        temp[k] = arr[j];
        j++;
        k++;
      }
      for (int p = start; p <= end; p++) {
        arr[p] = temp[p];
      }
    }

void MainWindow::swap(int & x, int & y)
{
    int temp = x;
    x = y;
    y = temp;
}

void MainWindow::on_STLSort_2_clicked()
{
    ui->error->setText("");
    chrono::steady_clock::time_point now = chrono::steady_clock::now();

    ui->view->clear();
    sort(arr, arr+size);
    chrono::steady_clock::time_point then = chrono::steady_clock::now();
    this->sortTime = chrono::duration_cast<chrono::nanoseconds>(then-now).count();

    for(int i=0;i<size;i++)
    {
       ui->view->addItem(QString::number(i) + ": " + QString::number(arr[i]));
    }
    ui->sortedOrNot->setText("Sorted Using STL Sort");


    ui->status->setText("STL Sort\nDuration time of search: " + QString::number(this->searchTime));
    ui->status->setText(ui->status->text() + "\nDuration time  of sorting: " + QString::number(this->sortTime));
    m.setText(ui->status->text());
    m.exec();
    ui->status->clear();
    SortingType = "STL Sort";
    ui->info->setText("Dataset size: " + QString::number(size) + "\n\nSorting Type: " + SortingType + "\n\nSearch Type: " + SearchType);
}


void MainWindow::on_MergeSort_2_clicked()
{
    ui->error->setText("");
    ui->view->clear();
    chrono::steady_clock::time_point now = chrono::steady_clock::now();
    mergesort(arr,0,size-1);
    chrono::steady_clock::time_point then = chrono::steady_clock::now();
    this->sortTime = chrono::duration_cast<chrono::nanoseconds>(then-now).count();
    for(int i=0;i<size;i++)
    {
       ui->view->addItem(QString::number(i) + ": " + QString::number(arr[i]));
    }
    ui->sortedOrNot->setText("Sorted Using Merge Sort");


    ui->status->setText("Merge Sort\nDuration time of search: " + QString::number(this->searchTime));
    ui->status->setText(ui->status->text() + "\nDuration time of sorting: " + QString::number(this->sortTime));
    m.setText(ui->status->text());
    m.exec();
    ui->status->clear();
    SortingType = "Merge Sort";
    ui->info->setText("Dataset size: " + QString::number(size) + "\n\nSorting Type: " + SortingType + "\n\nSearch Type: " + SearchType);
}


void MainWindow::on_normalSearch_2_clicked()
{
    NS=true,BS=false,STLS=false;
    SearchType = "Normal Search";
    ui->error->setText("");
    ui->info->setText("Dataset size: " + QString::number(size) + "\n\nSorting Type: " + SortingType + "\n\nSearch Type: " + SearchType);
}


void MainWindow::on_binarySearch_2_clicked()
{
    if(ui->sortedOrNot->text()!="unsorted array")
        { NS=false,BS=true,STLS=false;
             ui->error->setText("");
             SearchType = "Binary Search";
             ui->info->setText("Dataset size: " + QString::number(size) + "\n\nSorting Type: " + SortingType + "\n\nSearch Type: " + SearchType);

        }
        else
        {
            ui->error->setText("array must be sorted first!");
        }

}


void MainWindow::on_generateDataset_2_clicked()
{
    size = ui->size->text().toInt();
        ui->error->setText("");
        if(exists)
        {
            delete arr;
            arr = new int [size];
        }
        else
        {
            arr = new int [size];
            exists = true;
        }
        if (view)
        {
        ui->view->clear();
        ui->sortedOrNot->setText("unsorted array");
        }
        else
        {
            view = true;
        }
        for (int i = 0; i<size;i++)
        {
            arr[i]=rand()%size+1;
            ui->view->addItem(QString::number(i) + ": " + QString::number(arr[i]));
        }
        ui->info->setText("Dataset size: " + QString::number(size) + "\n\nSorting Type: " + SortingType + "\n\nSearch Type: " + SearchType);


}


void MainWindow::on_FindIt_clicked()
{
    ui->error->setText("");
       int num = ui->number->text().toInt();
       chrono::steady_clock::time_point now = chrono::steady_clock::now();
       if(NS)
       {
           NormalSearch(num);
       }
       else
       {
           BinarySearch(arr,num,0,size-1);
       }

       chrono::steady_clock::time_point then = chrono::steady_clock::now();
       this->searchTime = chrono::duration_cast<chrono::nanoseconds>(then-now).count();
       ui->status->setText(ui->status->text() + "\nDuration time of search: " + QString::number(this->searchTime));
       ui->status->setText(ui->status->text() + "\nDuration time of Sorting: " + QString::number(this->sortTime));
       m.setText(ui->status->text());
       m.exec();
       ui->status->clear();

}

