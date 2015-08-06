/*
 * Copyright (c) 2014-2015, dennis wang
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MISC_API_H
#define MISC_API_H

#include "config.h"

/**
 * ��ȡ��ǰ����
 */
extern uint32_t time_get_milliseconds();

/**
 * ��ȡ��ǰ΢��
 */
extern uint64_t time_get_microseconds();

/**
 * gettimeofday
 * @sa gettimeofday
 */
extern int time_gettimeofday(struct timeval *tp, void *tzp);

/**
 * ȡ�õ�ǰ���Ķ�ʱ���ַ���
 * @param buffer ���������
 * @param size ��������С
 * @return ��ʽΪYYYY-MM-DD HH:mm:SS:MS
 */
extern char* time_get_string(char* buffer, int size);

/**
 * ����һ��αUUID��ֻ��֤�������ڲ��ظ�
 * @return αUUID
 */
extern uint64_t uuid_create();

/**
 * ȡ��UUID��32λ
 * @param uuid UUID
 * @return ��32λ
 */
extern uint32_t uuid_get_high32(uint64_t uuid);

/**
 * ȡ�õ�ǰ����Ŀ¼
 * @param buffer ·��������ָ��
 * @param size ��������С
 * @retval 0 ʧ��
 * @retval ·��������ָ��
 */
extern char* path_getcwd(char* buffer, int size);

/**
 * ��ȡ���µ�ϵͳ������
 * @return ϵͳ������
 */
extern sys_error_t sys_get_errno();

/**
 * �ֽ���ת�� - ������������
 * @param ui64 64λ�޷�������
 * @return 64λ�޷�������
 */
extern uint64_t htonll(uint64_t ui64);

/**
 * �ֽ���ת�� - ������������
 * @param ui64 64λ�޷�������
 * @return 64λ�޷�������
 */
extern uint64_t ntohll(uint64_t ui64);

/**
 * ȡ�ùܵ��ص��¼�����
 * @param e �ܵ��ص��¼�ID
 * @return �ܵ��ص��¼�����
 */
extern const char* get_channel_cb_event_string(knet_channel_cb_event_e e);

/**
 * ȡ�ùܵ��ص��¼�����
 * @param e �ܵ��ص��¼�ID
 * @return �ܵ��ص��¼�����
 */
extern const char* get_channel_cb_event_name(knet_channel_cb_event_e e);

/**
 * longתΪchar*
 * @param l long
 * @param buffer �洢ת�����ַ���
 * @param size ����������
 * @retval 0 ʧ��
 * @retval ���� �ɹ�
 */
extern char* knet_ltoa(long l, char* buffer, int size);

/**
 * long long תΪchar*
 * @param ll long long
 * @param buffer �洢ת�����ַ���
 * @param size ����������
 * @retval 0 ʧ��
 * @retval ���� �ɹ�
 */
extern char* knet_lltoa(long long ll, char* buffer, int size);

/**
 * �ָ��ַ���
 * @param src ���ָ��ַ���
 * @param delim �ָ��ַ�
 * @param n �ָ���Ӵ�����
 * @retval 0 �ɹ�
 * @retval ���� ʧ��
 */
extern int split(const char* src, char delim, int n, ...);

#endif /* MISC_API_H */