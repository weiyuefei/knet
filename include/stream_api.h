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

#ifndef STREAM_API_H
#define STREAM_API_H

#include "config.h"

/**
 * @defgroup stream ��
 * �ܵ���
 *
 * <pre>
 * �ܵ���
 *
 * kstream_tͨ�����ú���knet_channel_ref_get_streamȡ��. �ܵ����ṩ�˻����������ݲ���
 * �Լ����������Եķ���������߲���Ч��.
 * 
 * 1. knet_stream_available   ��ȡ���ڿɶ��ֽ���
 * 2. knet_stream_eat_all     �����������пɶ��ֽ�
 * 3. knet_stream_eat         ��������ָ���������ֽ�
 * 4. knet_stream_pop         �����ڶ�ȡ����
 * 5. knet_stream_push        ������д����
 * 6. knet_stream_copy        �����ڿ���ָ�������Ŀɶ��ֽڣ����������Щ�ֽڣ�ͨ������Э����
 * 7. knet_stream_push_stream ���������пɶ��ֽ�д����һ����������Ҫ���⿽��, ���������ص�������ת
 * 8. knet_stream_copy_stream ���������пɶ��ֽ�д����һ����������Ҫ���⿽��, ���������Щ�ֽڣ������ڹ㲥
 *
 * ������Щ��������Ƴ��˻������������Ĺ������⣬���������ض������Ӧ�ã�ͬʱ�����Ч��.
 *
 * </pre>
 * @{
 */

/**
 * ȡ���������ڿɶ��ֽ���
 * @param stream kstream_tʵ��
 * @return �ɶ��ֽ���
 */
extern int knet_stream_available(kstream_t* stream);

/**
 * ���������
 * @param stream kstream_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_stream_eat_all(kstream_t* stream);

/**
 * ɾ��ָ����������
 * @param stream kstream_tʵ��
 * @param size ��Ҫɾ���ĳ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_stream_eat(kstream_t* stream, int size);

/**
 * ���������ڶ�ȡ���ݲ��������
 * @param stream kstream_tʵ��
 * @param buffer ������
 * @param size ��������С
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_stream_pop(kstream_t* stream, void* buffer, int size);

/**
 * ����������д����
 * @param stream kstream_tʵ��
 * @param buffer ������
 * @param size ��������С
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_stream_push(kstream_t* stream, const void* buffer, int size);

/**
 * ��������д���ݣ��ɱ�����ַ���
 *
 * һ��д��ĳ��Ȳ��ܳ���1024
 * @param stream kstream_tʵ��
 * @param format �ַ�����ʽ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_stream_push_varg(kstream_t* stream, const char* format, ...);

/**
 * ���������ڿ������ݣ��������������������
 * @param stream kstream_tʵ��
 * @param buffer ������
 * @param size ��������С
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_stream_copy(kstream_t* stream, void* buffer, int size);

/**
 * ��stream������д��target, �����stream������
 * @param stream kstream_tʵ��
 * @param target kstream_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_stream_push_stream(kstream_t* stream, kstream_t* target);

/**
 * ��stream������д��target, �������stream������
 * @param stream kstream_tʵ��
 * @param target kstream_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_stream_copy_stream(kstream_t* stream, kstream_t* target);

/**
 * ��ȡ�������Ĺܵ�����
 * @param stream kstream_tʵ��
 * @return kchannel_ref_tʵ��
 */
extern kchannel_ref_t* knet_stream_get_channel_ref(kstream_t* stream);

/** @} */

#endif /* STREAM_API_H */