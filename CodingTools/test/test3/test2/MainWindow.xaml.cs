using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
namespace test2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            this.DataContext = new UnitViewModel();
        }

        public static void DynamicAdd(Panel Container, UIElement Control)
        {

            Container.Children.Add(Control);

        }

        private void button_click(object sender, RoutedEventArgs e)
        {
            Debug.WriteLine("btttttttt");
        }

        private void buttonAdd_Click(object sender, RoutedEventArgs e)
        {



            Button btn = new Button();

            btn.Width = 60;

            btn.Height = 30;
            btn.Content = "ddd";

            //设置按钮样式使用此种方法必须将资源文件引用到当前页面  

            btn.Style = Resources["NoticeButton"] as Style;
            btn.Click += button_click;

            //此种方法也可以设置样式  

            //获取App.xaml中的样式个人更喜欢这种  

            //Style style = (Style)this.FindResource("NoticeButton");  

            //为按钮设置样式  

            //btn.Style = style;  

            //将btn添加到ufg  

            DynamicAdd(wrp, btn);

        }  
    }
}
