
    printf("[%s]\n", __PRETTY_FUNCTION__);
}


////
///Main Program
int main(){
    {
    Point2D P0;// com os valores iniciais
    Point2D* p=new Point2D(10,20, "Pdynamic");
    }
    printf("%p\n", p);
    Point2D P1(1,2,"P1");
}