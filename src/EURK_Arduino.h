/*
  �ѱ� ���̺귯�� '��췯��' �Ƶ��̳� ���� 1.0
  ���� : OLED ���÷��̸� ����ϴ� �Ƶ��̳� ���α׷����� �ѱ� ����� �����Ӱ� �ϱ� ����
         ���������.
  ��� ���̺귯�� : Adafruit���� ������ OLED ���÷��̿� ���̺귯����
                    Adafruit_GFX, Adafruit_SSD1306
  ��� ��� : ��� (�� ����) ���̺귯���� '(�����)/����/Arduino/libraries' ������ ��ġ�ϰ�,
              �ҽ� ���Ͽ��� EURK_Arduino.h ��� ������ ��Ŭ����� �Ŀ�,
              ���÷��� ��Ȳ�� ���� display ������Ʈ�� �����ϰ� ����,
              ������ �ѱ� ���̺귯�� �Լ����� ȣ���ϸ� �ȴ�.
  ���� : �����̷�������� ( http://sookmook.org )
  ���� ��� : ���� ������ ( mailto://sookmook@sookmook.org )
              feat. �Ⱥ��� ( mailto://hayansea@sookmook.org )
  ���� ��¥ : 2018�� 4�� 24��
*/

#ifndef __EURK_ARDUINO_H
#define __EURK_ARDUINO_H

#include <Adafruit_GFX.h>

#ifdef USE_EURK_ON_LINUX
#include "ArduiPi_OLED.h"
#include <vector>
#else
#include <Adafruit_SSD1306.h>
#endif

#include "sfif_inc.h"
#include "Hangeul_Font.h"
#include "ASCII_Font.h"

#ifdef USE_EURK_ON_LINUX

// macros from Adafruit_GFX.cpp
// Many (but maybe not all) non-AVR board installs define macros
// for compatibility with existing PROGMEM-reading AVR code.
// Do our own checks and defines here for good measure...

#ifndef pgm_read_byte
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

#endif

/* 2����Ʈ ������ �ѱ��� ���� ����ü */
#ifndef __HAN_UNION
#define __HAN_UNION
union HAN_UNION {
  struct {
    word l : 5 ;
    word m : 5 ;
    word f : 5 ;
    word s : 1 ;
  } a ; /* �ڸ� */
  struct {
    byte s ;
    byte f ;
  } c ; /* �ڵ� */
} ;
#endif

/* ���뱹��� ǥ�� ������ ��� �ѱ��� �� = 11172 */
/* (�ʼ� 19 * �߼� 21 * ����(��ħ ���� �� ����) 28 */
#ifndef ALL_OF_HAN
#define ALL_OF_HAN 11172
#endif

/* �ѱ� �ڵ� ���� */
#ifndef __HANCODE__DEFINE
#define __HANCODE__DEFINE
#define HANCODE_UTF_8       0
#define HANCODE_EXTENED_KSC 1
#endif

/* �����ڵ忡�� �ѱ��� ���� ��ġ */
#ifndef UNICODE_HAN_BASE
#define UNICODE_HAN_BASE 0xAC00
#endif

void EURK_hancode(int kind) ;
void EURK_setxy(int x, int y) ;
#ifdef USE_EURK_ON_LINUX
void EURK_puts(char *s, int tag_type, std::vector<double> scroll, double secs) ;
void EURK_putsxy(int x, int y, char *s, int tag_type, std::vector<double> scroll, double secs) ;
#else
void EURK_puts(char *s) ;
void EURK_putsxy(int x, int y, char *s) ;
#endif

#endif
