package com.example.myapplication;

import android.app.Activity;
import android.util.Log;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Vector;

public class FileUtil {
    private static FileUtil instance = new FileUtil();

    public static FileUtil getInstance() {
        return instance;
    }

    public static ArrayList<Float> readPointCloud(Activity activity, String fileName, float[] bounds) {
        float maxX = Float.MIN_VALUE;
        float maxY = Float.MIN_VALUE;
        float maxZ = Float.MIN_VALUE;
        float minX = Float.MAX_VALUE;
        float minY = Float.MAX_VALUE;
        float minZ = Float.MAX_VALUE;
        ArrayList<Float> list = new ArrayList<>();
        BufferedReader buffReader = null;
        InputStream inputStream = null;
        InputStreamReader fileReader = null;
        try {
            inputStream = activity.getAssets().open(fileName);
            fileReader = new InputStreamReader(inputStream);
            buffReader = new BufferedReader(fileReader);
            String str = null;
//            float[] doubles = new float[3];
            while ((str = buffReader.readLine()) != null) {
                String[] strs = str.split(",");
                if (strs.length == 3) {
                    for (int i = 0; i < strs.length; i++) {
                        float value = Float.parseFloat(strs[i]);
                        list.add(value);
                        if (i == 0) {
                            maxX = Math.max(maxX,value);
                            minX = Math.min(minX,value);
                        } else if (i == 1) {
                            maxY = Math.max(maxY,value);
                            minY = Math.min(minY,value);
                        } else if (i == 2) {
                            maxZ = Math.max(maxZ,value);
                            minZ = Math.min(minZ,value);
                        }
                    }

                } else {
                    list.add(0.0f);
                    list.add(0.0f);
                    list.add(0.0f);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (inputStream != null) {
                    inputStream.close();
                    inputStream = null;
                }
                if (fileReader != null) {
                    fileReader.close();
                    fileReader = null;
                }
                if (buffReader != null) {
                    buffReader.close();
                    buffReader = null;
                }
            } catch (Exception e) {
            }
        }
        bounds[0] = minX;
        bounds[1] = minY;
        bounds[2] = minZ;
        bounds[3] = maxX;
        bounds[4] = maxY;
        bounds[5] = maxZ;
        return list;
    }
}
