using Leap.Unity;
using Leap;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Numerics;
using TMPro;
using UnityEngine.UI;

public class joint_logger : MonoBehaviour
{
    public LeapProvider leapProvider;
    public TMP_Text myText;
    // Start is called before the first frame update
    public int indexAng;
    public int indexRot;
    public int thumbAng;
    public int thumbRot;
    public int ringAng;
    public int ringRot;
    public int middleAng;
    public int middleRot;



    void Start()
    {

        
    }

    private void OnEnable()
    {
        leapProvider.OnUpdateFrame += OnUpdateFrame;
    }
    private void OnDisable()
    {
        leapProvider.OnUpdateFrame -= OnUpdateFrame;
    }

    void OnUpdateFrame(Frame frame)
    {
        //Use a helpful utility function to get the first hand that matches the Chirality
        Hand _leftHand = frame.GetHand(Chirality.Left);

        //When we have a valid left hand, we can begin searching for more Hand information
        if (_leftHand != null)
        {
            OnUpdateHand(_leftHand);
        }
    }

    void OnUpdateHand(Hand _hand)
    {
        Finger _thumb = _hand.GetThumb();
        Finger _index = _hand.GetIndex();
        Finger _middle = _hand.GetMiddle();
        Finger _ring = _hand.GetRing();


        Bone _thumbMetacarpal = _thumb.Bone(Bone.BoneType.TYPE_METACARPAL);
        Bone _indexMetacarpal = _index.Bone(Bone.BoneType.TYPE_METACARPAL);
        Bone _middleMetacarpal = _middle.Bone(Bone.BoneType.TYPE_METACARPAL);
        Bone _ringMetacarpal = _ring.Bone(Bone.BoneType.TYPE_METACARPAL);

        //Use the _finger to subsequently get the Metacarpa bone from it using the BoneType Enum
        Bone _thumbPROXIMAL = _thumb.Bone(Bone.BoneType.TYPE_PROXIMAL);
        Bone _indexPROXIMAL = _index.Bone(Bone.BoneType.TYPE_PROXIMAL);
        Bone _middlePROXIMAL = _middle.Bone(Bone.BoneType.TYPE_PROXIMAL);
        Bone _ringPROXIMAL = _ring.Bone(Bone.BoneType.TYPE_PROXIMAL);

        Bone _thumbINT = _thumb.Bone(Bone.BoneType.TYPE_INTERMEDIATE);
        Bone _indexINT = _index.Bone(Bone.BoneType.TYPE_INTERMEDIATE);
        Bone _middleINT = _middle.Bone(Bone.BoneType.TYPE_INTERMEDIATE);
        Bone _ringINT = _ring.Bone(Bone.BoneType.TYPE_INTERMEDIATE);


        indexAng = (int)UnityEngine.Vector3.SignedAngle(_indexPROXIMAL.Direction, _indexINT.Direction, UnityEngine.Vector3.forward);
        indexRot = (int)UnityEngine.Vector3.SignedAngle(UnityEngine.Vector3.ProjectOnPlane(_indexMetacarpal.Direction, UnityEngine.Vector3.up), UnityEngine.Vector3.ProjectOnPlane(_indexPROXIMAL.Direction, UnityEngine.Vector3.up), UnityEngine.Vector3.up);

        thumbAng = (int)UnityEngine.Vector3.SignedAngle(_thumbPROXIMAL.Direction, _thumbINT.Direction, UnityEngine.Vector3.forward);
        thumbRot = (int)UnityEngine.Vector3.SignedAngle(UnityEngine.Vector3.ProjectOnPlane(_thumbMetacarpal.Direction, UnityEngine.Vector3.up), UnityEngine.Vector3.ProjectOnPlane(_thumbPROXIMAL.Direction, UnityEngine.Vector3.up), UnityEngine.Vector3.up);

        ringAng = (int)UnityEngine.Vector3.SignedAngle(_ringPROXIMAL.Direction, _ringINT.Direction, UnityEngine.Vector3.forward);
        ringRot = (int)UnityEngine.Vector3.SignedAngle(UnityEngine.Vector3.ProjectOnPlane(_ringMetacarpal.Direction, UnityEngine.Vector3.up), UnityEngine.Vector3.ProjectOnPlane(_ringPROXIMAL.Direction, UnityEngine.Vector3.up), UnityEngine.Vector3.up);

        middleAng = (int)UnityEngine.Vector3.SignedAngle(_middlePROXIMAL.Direction, _middleINT.Direction, UnityEngine.Vector3.forward);
        middleRot = (int)UnityEngine.Vector3.SignedAngle(UnityEngine.Vector3.ProjectOnPlane(_middleMetacarpal.Direction, UnityEngine.Vector3.up), UnityEngine.Vector3.ProjectOnPlane(_middlePROXIMAL.Direction, UnityEngine.Vector3.up), UnityEngine.Vector3.up);


        Debug.Log(indexRot);


    }

    // Update is called once per frame
    void Update()
    {
        myText.text = "Front left Base: " + middleAng.ToString() + "\n" +
            "Front Left Foot: " + middleRot.ToString() + "\n" +
            "Front Right Base: " + indexAng.ToString() + "\n" + 
            "Front Right Foot: " + indexRot.ToString() + "\n" + 
            "Back Left Base: " + ringAng.ToString() + "\n" + 
            "Back Left Foot: " + ringRot.ToString() + "\n" + 
            "Back Right Base: " + thumbAng.ToString() + "\n" + 
            "Back Right Foot: " + thumbRot.ToString() + "\n";


    }
}
