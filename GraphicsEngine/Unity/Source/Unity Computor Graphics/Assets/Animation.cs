using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Animation : MonoBehaviour {

    Animator animate;

	// Use this for initialization
	void Start () {
        animate = GetComponent<Animator>();
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown(KeyCode.W))
        {
            animate.SetBool("isWalking", true);

        }
        else
        {
            animate.SetBool("IsWalking", false);
        }
	}
}
