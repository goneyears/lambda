using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using TCPClient;
public class Clock : MonoBehaviour {

    // Use this for initialization

    TCP_Client tcp = new TCP_Client("192.168.31.23", "30000");
    void Start () {
        tcp.Send("hehehe");
        tcp.MessageReceived += GetCommand;
	}
	
    public string command { get; set; }
    void GetCommand(System.Object sender, TCPEventArgs e)
    {
        command = e.receivedmessage;
        Debug.Log(command);
        if(command == "1")
        {
            Debug.Log("is 1");
        }
        Debug.Log(command == "1");
    }
	// Update is called once per frame


    public Transform hoursTransform, minutesTransform, secondsTransform;
    public bool continuous;

    const float degreesperhour = 30f;
    const float degreesperminute = 6f;
    const float degreesperseconds = 6f;
    void Update()
    {
        if (continuous)
        {
            UpdateContinuous();
        }
        else
        {
            UpdateDiscrete();
        }
    }
    void UpdateDiscrete()
    {
        if (DateTime.Now.Second == 10)
        {
            Debug.Log(DateTime.Now.Second);
        }
        if(command == "1")
        {
            ///Debug.Log("is 1");
            DateTime time = DateTime.Now;
            hoursTransform.localRotation = Quaternion.Euler(0f, DateTime.Now.Hour * degreesperhour, 0f);
            minutesTransform.localRotation = Quaternion.Euler(0f, DateTime.Now.Minute * degreesperminute, 0f);
            secondsTransform.localRotation = Quaternion.Euler(0f, DateTime.Now.Second * degreesperseconds, 0f);
        }
    }
    void UpdateContinuous()
    {
        //Debug.Log(DateTime.Now);
        TimeSpan time = DateTime.Now.TimeOfDay;
        hoursTransform.localRotation = Quaternion.Euler(0f, (float)time.TotalHours * degreesperhour, 0f);
        minutesTransform.localRotation = Quaternion.Euler(0f, (float)time.TotalMinutes * degreesperminute, 0f);
        secondsTransform.localRotation = Quaternion.Euler(0f, (float)time.TotalSeconds * degreesperseconds, 0f);
    }
}
