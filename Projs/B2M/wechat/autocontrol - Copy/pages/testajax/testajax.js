Page({

  data: {

    motto: '你懂我懂不懂',

    list: 1

  },

  onload: function () {

    this.onRequest();

  },

  onRequest: function () {

    var that = this;

    wx.request({

      //url: 'https://api.douban.com/v2/movie/top250',
      //url: 'https://douban.uieee.com/v2/movie/top250',
      //data: {//发送给后台的数据

      //},
      url: 'http://123.206.125.181:8000/add/',//请求地址

      data: {//发送给后台的数据
        a: 1,
        b: 20
      },
      header: {//请求头
        //"Content-Type": "applciation/json"
      },
      method: "GET",

      header: {
        //name: 'referrer',
        //content: 'never'
        'Content-Type': 'json'

      },

      success: function (res) {

        console.log(res.data);

        var date = res.data;

        //that.setData({

        //  list: date

        //})


        var listarr = new Array();
        listarr[0] = res.data;//////
        //for (var index = 0; index < listarr.length; index++) {
          console.log('ok')
          that.setData({ 'list' : listarr[0] })
        //};
        //console.log(list);

      },

      fail: function () {

        console.log("接口调用失败");

      }

    })

  },

  nextPage: function () {

    console.log("下拉触发该函数");

  },

  //事件处理函数

  bindViewTap: function () {

    wx.navigateTo({

      url: '../logs/logs'

    })

  },



  Countdown: function() {
    var that=this;
    setTimeout(function () {
      console.log("----Countdown----");
      that.onRequest();
      that.Countdown();
    }, 1000);
  },
  startBtn: function () {
    console.log("开始按钮");
    this.Countdown();
  },
})