using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System;
using System.Linq;

public class data_sender : MonoBehaviour
{
    
    
    // Start is called before the first frame update
    void Start()
    {
        
        

     

    }

    // Update is called once per frame
    void Update()
    {
        UdpClient udpClient = new UdpClient();
        byte[] data = new byte[8];
        data[0] = 25;
        try
        {
            udpClient.Send(data, 1, "192.168.4.1", 11000);
        }
        catch (Exception e)
        {
            Debug.Log(e.ToString());
        }
    }
}
