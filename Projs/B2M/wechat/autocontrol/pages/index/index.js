var wxCharts = require('../../utils/wxchartsring.js');
var app = getApp();
var ringChart = null;


Page({

  data: {
    test_count: 1,
    test_ratio: '70%'
  },

  onLoad: function () {

    console.log("开始");
    this.Countdown();
    //this.onRequest();

  },

  onRequest: function () {

    var that = this;

    wx.request({
      url: 'http://123.206.125.181:8000/getdata/',//请求地址
      data: {//发送给后台的数据
        type: 'daycount'
      },
      method: "GET",
      header: {
        'Content-Type': 'json'

      },

      success: function (res) {

        console.log(res.data);

        var date = res.data;
        var listarr = new Array();
        listarr[0] = res.data;//
        console.log('ok')
        that.setData({ 'test_count': listarr[0] })
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

  bindShowPie: function () {
    wx.navigateTo({
      url: '../charts/ring/ring',
    })
  },



  Countdown: function () {
    var that = this;
    setTimeout(function () {
      console.log("----Countdown----");
      that.onRequest();
      that.updateData();
      //that.Countdown();
    }, 2000);
  },
  startBtn: function () {
    console.log("开始按钮");
    this.Countdown();
  },



  //ring display
  touchHandler: function (e) {
    console.log(ringChart.getCurrentDataIndex(e));
  },
  updateData: function () {
    var cc = this.data.test_ratio;
    console.log(this.data.test_ratio);
    ringChart.updateData({
      title: {
        name: cc
      },
      subtitle: {
        color: '#ff0000'
      }
    });
  },
  onReady: function (e) {
    var windowWidth = 320;
    try {
      var res = wx.getSystemInfoSync();
      windowWidth = res.windowWidth;
    } catch (e) {
      console.error('getSystemInfoSync failed!');
    }

    ringChart = new wxCharts({
      animation: true,
      canvasId: 'ringCanvas',
      type: 'ring',
      extra: {
        ringWidth: 25,
        pie: {
          offsetAngle: -45
        }
      },
      title: {
        name: ' ',
        color: '#7cb5ec',
        fontSize: 25
      },
      subtitle: {
        name: '日产量',
        color: '#666666',
        fontSize: 15
      },
      series: [{
        name: '成交量1',
        data: 15,
        stroke: false
      }, {
        name: '成交量2',
        data: 35,
        stroke: false
      }, {
        name: '成交量3',
        data: 78,
        stroke: false
      }, {
        name: '成交量4',
        data: 63,
        stroke: false
      }],
      disablePieStroke: true,
      width: windowWidth,
      height: 200,
      dataLabel: false,
      legend: false,
      background: '#f5f5f5',
      padding: 0
    });
    ringChart.addEventListener('renderComplete', () => {
      console.log('renderComplete');
    });
    setTimeout(() => {
      ringChart.stopAnimation();
    }, 1000);
  },



  bindDetailTap: function () {

    wx.navigateTo({

      url: '../list/list'

    })

  },
})