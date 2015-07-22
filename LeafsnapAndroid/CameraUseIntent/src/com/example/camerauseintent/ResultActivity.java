package com.example.camerauseintent;

import java.util.ArrayList;
import java.util.HashMap;

import com.example.camerauseintent.MainActivity.MyButtonListener2;

import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ListView;

public class ResultActivity extends ListActivity {
	private String LeafList[] = {"合欢花", "加拿大一枝黄花", "黑桦","金樱子山楂",
			"银杏", "广玉兰", "杨树", "柳树", "枳树", "红松"};
	private static final ArrayList list = new ArrayList();
	private Button returnButton;
    /** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.result);
		returnButton = (Button)findViewById(R.id.returnButton);
		returnButton.setOnClickListener(new returnButtonListener());
		
		//通过Intent可以从上一个Activity中获取到result byte[]的值
		Intent intent = getIntent();
		String result = intent.getStringExtra("result");
		
		//List的Map元素
		ArrayList<HashMap<String, Object>> list = new ArrayList<HashMap<String, Object>>();
		HashMap<String, Object> map1 = new HashMap<String, Object>();
		HashMap<String, Object> map2 = new HashMap<String, Object>();
		HashMap<String, Object> map3 = new HashMap<String, Object>();
		HashMap<String, Object> map4 = new HashMap<String, Object>();
		HashMap<String, Object> map5 = new HashMap<String, Object>();
		//根据result数组将相应的名字和图片放入map当中
		int number;	int resID;
		number = result.charAt(0) - '0';
		map1.put("leaf_name", LeafList[number]);
		resID = getResources().getIdentifier("leaf_"+number, "drawable", "com.example.camerauseintent"); 
		map1.put("leaf_pic", resID);
		
		number = result.charAt(1) - '0';
		map2.put("leaf_name", LeafList[number]);
		resID = getResources().getIdentifier("leaf_"+number, "drawable", "com.example.camerauseintent"); 
		map2.put("leaf_pic", resID);
		
		number = result.charAt(2) - '0';
		map3.put("leaf_name", LeafList[number]);
		resID = getResources().getIdentifier("leaf_"+number, "drawable", "com.example.camerauseintent"); 
		map3.put("leaf_pic", resID);
		
		number = result.charAt(3) - '0';
		map4.put("leaf_name", LeafList[number]);
		resID = getResources().getIdentifier("leaf_"+number, "drawable", "com.example.camerauseintent"); 
		map4.put("leaf_pic", resID);
		
		number = result.charAt(4) - '0';
		map5.put("leaf_name", LeafList[number]);
		resID = getResources().getIdentifier("leaf_"+number, "drawable", "com.example.camerauseintent"); 
		map5.put("leaf_pic", resID);
		
		list.add(map1);
		list.add(map2);
		list.add(map3);
		list.add(map4);
		list.add(map5);
		MyAdapter listAdapter = new MyAdapter(this, list,
				R.layout.user, new String[] { "leaf_name", "leaf_pic" },
				new int[] { R.id.leaf_name,R.id.leaf_pic});
		setListAdapter(listAdapter);
	}
	
	class returnButtonListener implements OnClickListener{
		@Override
		public void onClick(View v) {
			Intent intent = new Intent();
			intent.setClass(ResultActivity.this, MainActivity.class);
			ResultActivity.this.startActivity(intent);
		}
	}

	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		// TODO Auto-generated method stub
		super.onListItemClick(l, v, position, id);
		System.out.println("id----------------" + id);
		System.out.println("position----------" + position);
	}
}
