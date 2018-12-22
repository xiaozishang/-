//index.js
//获取应用实例

Page({
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    //加载时就获取后台的数据
    this.get_data()
  },
  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  },
  send4: function () {
    this.setData({
      datao: this.data.datao
    })
    wx.showToast({
      title: "SEND SUCCESS",
      duration: 1000
    })
    this.sendRequset(this.makeObj(this.data.datao, this.data.datat, this.data.datath, ""));
  },
  send2: function (datat) {
    var _this = this;
    wx.request({
      url: 'http://api.heclouds.com/devices/503092674/datapoints?type=3',
      header: {
        "Content-Type": "application/json",
        "api-key": "WgySE7y=0=BzIjL6WxErlSsi4dQ="
        // "Host": "api.heclouds.com"
      },
      method: 'post',
      data: {
        datat: "1"
      },
      success: function (res) {
        console.log(res)
      },
      fail: function (res) {
        console.log(res)
      }
    })

  },

  
  send1: function () {

    this.getDataFromOneNet1;
  },
  send5: function (datath) {
    var _this = this;
    wx.request({
      url: 'http://api.heclouds.com/devices/503092674/datapoints?type=3',
      header: {
        "Content-Type": "application/json",
        "api-key": "WgySE7y=0=BzIjL6WxErlSsi4dQ="
        // "Host": "api.heclouds.com"
      },
      method: 'post',
      data: {
        datath: "1"
      },
      success: function (res) {
        console.log(res)
      },
      fail: function (res) {
        console.log(res)
      }
    })
  },
  send6: function (datath) {
    var _this = this;
    wx.request({
      url: 'http://api.heclouds.com/devices/503092674/datapoints?type=3',
      header: {
        "Content-Type": "application/json",
        "api-key": "WgySE7y=0=BzIjL6WxErlSsi4dQ="
        // "Host": "api.heclouds.com"
      },
      method: 'post',
      data: {
        datath: "0"
      },
      success: function (res) {
        console.log(res)
      },
      fail: function (res) {
        console.log(res)
      }
    })
  },
  send7: function (datat) {
    var _this = this;
    wx.request({
      url: 'http://api.heclouds.com/devices/503092674/datapoints?type=3',
      header: {
        "Content-Type": "application/json",
        "api-key": "WgySE7y=0=BzIjL6WxErlSsi4dQ="
        // "Host": "api.heclouds.com"
      },
      method: 'post',
      data: {
        datat: "0"
      },
      success: function (res) {
        console.log(res)
      },
      fail: function (res) {
        console.log(res)
      }
    })
  },
  //Function of the function is to auto move slide  ,every second ++
  change1: function (e) {
    //当有输入时激活发送按钮，无输入则禁用按钮
    if (e.detail.value != "") {
      this.setData({
        datao: e.detail.value,

      })
    }

  },
  /*change2: function (e) {
    
      this.setData({
        datao: e.detail.value,

      })
    

  },
  change3: function (e) {
    
      this.setData({
        datao: e.detail.value,

      })
    

  },
  change4: function (e) {
    //当有输入时激活发送按钮，无输入则禁用按钮
    
      this.setData({
        datao: e.detail.value,

      })
    

  },*/
  sendRequset: function (obj) {
    wx.request(obj);
  },
  makeObj: function (data1, data2, data3, msg) {
    var obj = {
      url: "http://api.heclouds.com/devices/503092674/datapoints?type=3",

      header: {
        "Content-Type": "application/json",
        "api-key": "WgySE7y=0=BzIjL6WxErlSsi4dQ=",
        //"Host": "api.heclouds.com"
      },
      method: "post",
      data: {
        "datao": data1,
        "datat": data2,
        "datath": data3,
      },
      success: function (res) {
        if (msg != "") {
          wx.showToast({
            title: msg,
            duration: 2000
          })
          //console.log(i);
        }
      }
    }
    return obj;
  },
  get_data: function () {
    // 获取数据
    var that = this;
    wx.request({
      url: 'https://api.heclouds.com/devices/503092674/datapoints?datastream_id=datao,datat,datath&limit=1',
      header: {
        'content-type': 'application/json',
        'api-key': 'WgySE7y=0=BzIjL6WxErlSsi4dQ='
      },
      success: function (res) {
        console.log(res.data)
        wx.showToast({
          title: "OK",
          duration: 1000
        })



        console.log(res.data.data.datastreams[0].datapoints[0].value),
          console.log(res.data.data.datastreams[1].datapoints[0].value),
          console.log(res.data.data.datastreams[2].datapoints[0].value),
          that.setData({
            datao: res.data.data.datastreams[2].datapoints[0].value, 
            datat: res.data.data.datastreams[0].datapoints[0].value,
            datath: res.data.data.datastreams[1].datapoints[0].value,
          })


      }
    })
  },

})
