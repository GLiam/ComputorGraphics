using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Lights : MonoBehaviour {

    public Button lightsOn;

    public GameObject spotLight;
    public Light light;

	// Use this for initialization
	void Start ()
    {
        Button btn = lightsOn.GetComponent<Button>();
        //btn.onClick.AddListener(OnClick);

        GameObject lightObject = GameObject.Find("Spotlight");
        light = lightObject.GetComponent<Light>();
	}

    public void DoSomethingOnClick()
    {
        Debug.Log("clicked");
        light.enabled = !light.enabled;
    }
}
