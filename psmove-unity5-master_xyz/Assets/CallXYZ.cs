using UnityEngine;
using System.Collections;

public class CallXYZ : MonoBehaviour {

	// Use this for initialization
	void Start () {

	}

	// Update is called once per frame
	void Update () {
		float a = Mathf.Round (transform.position.x*1000.0f)/1000.0f;
		float b = Mathf.Round ((transform.position.y-0.251f)*1000.0f)/1000.0f;
		float c = Mathf.Round (transform.position.z*1000.0f)/1000.0f;
		Sending.sendXYZ(a,b,c);
	}

}