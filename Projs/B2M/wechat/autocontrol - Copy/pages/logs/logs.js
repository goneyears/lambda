//logs.js
const util = require('../../utils/util.js')

Page({
  data: {
    logs: ['ff','ss']
  },
  onLoad: function () {
    

      var that = this;   
      //这个地方非常重要，重置data{}里数据时候setData方法的this应为以及函数的this, 
      //如果在下方的sucess直接写this就变成了wx.request()的this了

      that.setData({ screenData: "ddd" });
      wx.request({
        url: 'http://123.206.125.181:8000/add/',//请求地址
        
        data: {//发送给后台的数据
          a: 1,
          b: 20
        },
        header: {//请求头
          //"Content-Type": "applciation/json"
        },
        method: "GET",//get为默认方法/POST
        success: function (res) {
          var listarr = new Array();
          //console.log((res.data).replace(/\(/g, '').replace(/\)/g, ''));
          //listarr = (res.data).replace(/\(/g, '').replace(/\)/g, '').split(',')
          //console.log(listarr)
          //res.data相当于ajax里面的data,为后台返回的数据
          var disp = "1\n2\n3\n";
          //logs = listarr
          //that.setData({ 'logs[0]': 'fff' });
          listarr[0]=res.data
          console.log("resdata: "+res.data)
          console.log(listarr.length)
          var item = that.data.logs[0]
          item = "dddddd"
          var index = 0
          for(var index = 0;index < listarr.length;index++)
          {
            console.log('ok')
            that.setData({ ['logs[' + index + ']']: listarr[index]})
          }
  
        },
        fail: function (err) { },//请求失败
        complete: function () { }//请求完成后执行的函数
      })

    
    //this.setData({
    // logs: (wx.getStorageSync('logs') || []).map(log => {
    //   return util.formatTime(new Date(log))
    // })
    //})
  }
})
