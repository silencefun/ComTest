/*
 * Copyright 2009 Cedric Priscal
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. 
 */

package com.silencefun.comtest.serialport;

import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.util.Log;

public class SerialPort {

    private static final String TAG = "SerialPort";

    /*
     * Do not remove or rename the field mFd: it is used by native method close();
     */
    private FileDescriptor mFd;
    private FileInputStream mFileInputStream;
    private FileOutputStream mFileOutputStream;

    public SerialPort(File device, int baudrate, int dataBits, int stopBits, char parity) throws SecurityException, IOException {


       // mFd = open(device.getAbsolutePath(), baudrate, flags);

        mFd = open(device.getAbsolutePath(), baudrate,dataBits,stopBits,parity);
        if (mFd == null) {
            Log.e(TAG, "native open returns null");
            throw new IOException();
        }
        mFileInputStream = new FileInputStream(mFd);
        mFileOutputStream = new FileOutputStream(mFd);
    }
    public SerialPort(File device, int baudrate, int flags) throws SecurityException, IOException {


        // mFd = open(device.getAbsolutePath(), baudrate, flags);

        mFd = open(device.getAbsolutePath(), baudrate,8,2,'E');
        if (mFd == null) {
            Log.e(TAG, "native open returns null");
            throw new IOException();
        }
        mFileInputStream = new FileInputStream(mFd);
        mFileOutputStream = new FileOutputStream(mFd);
    }
    // Getters and setters
    public InputStream getInputStream() {
        return mFileInputStream;
    }

    public OutputStream getOutputStream() {
        return mFileOutputStream;
    }

    // JNI
    private native static FileDescriptor open(String path, int baudrate, int flags);

    // 调用JNI中 打开方法的声明

    /**
     * @param dataBits 类型 int数据位 取值 位7或8
     * @param parity   char校验类型 取值N ,E, O,,S
     * @param stopBits 类型 int 停止位 取值1 或者 2
     * @return
     */
    private native static FileDescriptor open(String path, int baudrate, int dataBits, int stopBits, char parity);

    public native void close();

    static {
        System.loadLibrary("native-lib");
    }
}
