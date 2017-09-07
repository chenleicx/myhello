#include "hci_tts.h"
#include "common/FileReader.h"
#include "common/CommonTool.h"
#include <string>
#include "common/AccountInfo.h"
using std::string;

#ifdef __LINUX__
#include <stdio.h>
#endif

//�ϳɻص�������ͨ���˺������ϳɽ�����浽�ļ�
bool HCIAPI TtsSynthCallbackFunction(_OPT_ _IN_ void * pvUserParam,
                                     _MUST_ _IN_ TTS_SYNTH_RESULT * psTtsSynthResult,
                                     _MUST_ _IN_ HCI_ERR_CODE  hciErrCode);

//�ϳɺ���
void TTSSynth(const string &cap_key, const string &txt_file, const string &out_pcm_file );

//�����ܺ����ú����г�ʶ��ģ��������ģ�鲻֧�ֶ��̵߳��ã���������ʹ�ù�����Ӧ��ע����Ⲣ��
void FunctionFunc(const string &cap_key,const string &data_path,const string &test_data_path)
{
	HCI_ERR_CODE err_code = HCI_ERR_NONE;

	//TTS ��ʼ��
	string tts_init_config = "dataPath=";
    tts_init_config += data_path;
	tts_init_config += ",initCapkeys=";
	tts_init_config += cap_key;
	err_code = hci_tts_init(tts_init_config.c_str());
	if (err_code != HCI_ERR_NONE)
	{
		printf("hci_tts_init return (%d:%s) \n",err_code,hci_get_error_info(err_code));
		return;
	}

	// ���������ϳɲ����ļ�
	string file_to_synth;
	if (cap_key == "tts.local.synth.sing")
	{
		file_to_synth = test_data_path + "/S3ML_sing.txt.enc";
	}
	else
	{
		file_to_synth = test_data_path + "/tts.txt";
	}
	
	string out_pcm_file = test_data_path + "/synthResult.pcm";
	TTSSynth(cap_key, file_to_synth, out_pcm_file);

	//TTS����ʼ��
	hci_tts_release();
    printf("hci_tts_release\n");

	return;
}


//�ϳɻص�������ͨ���˺������ϳɽ�����浽�ļ�
bool HCIAPI TtsSynthCallbackFunction(_OPT_ _IN_ void * pvUserParam,
                                     _MUST_ _IN_ TTS_SYNTH_RESULT * psTtsSynthResult,
                                     _MUST_ _IN_ HCI_ERR_CODE  hciErrCode)
{
    if( hciErrCode != HCI_ERR_NONE )
    {
        return false;
    }

    //printf("voice data size %d\n",psTtsSynthResult->uiVoiceSize);
    // ���ϳɽ��д���ļ�
    if (psTtsSynthResult->pvVoiceData != NULL)
    {
        FILE * fp = (FILE *)pvUserParam;
        fwrite(psTtsSynthResult->pvVoiceData, psTtsSynthResult->uiVoiceSize, 1, fp);
    }

	//mark �ص����
	if (psTtsSynthResult->nMarkCount > 0)
	{
		for (int i=0; i<psTtsSynthResult->nMarkCount; ++i)
		{
			printf("MarkName:%s, with the time in audio:%d \n",psTtsSynthResult->pMark[i].pszName,psTtsSynthResult->pMark[i].time);
		}

	}

    // �˻ص���������false����ֹ�ϳɣ�����true��ʾ�����ϳ�
    return true;
}

void TTSSynth(const string &cap_key, const string &txt_file, const string &out_pcm_file )
{
    // �ϳ��ı���ȡ
    HciExampleComon::FileReader txt_data;
    if( txt_data.Load(txt_file.c_str(),1) == false )
    {
        printf( "Open input text file %s error!\n", txt_file.c_str() );
        return;
    }

    // ������ļ�
    FILE * fp = fopen( out_pcm_file.c_str(), "wb" );
    if( fp == NULL )
    {
        printf( "Create output pcm file %s error!\n", out_pcm_file.c_str());
        return;
    }

    HCI_ERR_CODE err_code = HCI_ERR_NONE;
    // ���� TTS Session
    string session_config = "capkey=";
    session_config += cap_key;
    int session_id = -1;

    printf( "hci_tts_session_start config [%s]\n", session_config.c_str() );
    err_code = hci_tts_session_start( session_config.c_str(), &session_id );
    if( err_code != HCI_ERR_NONE )
    {
        printf("hci_tts_session_start return (%d:%s) \n",err_code,hci_get_error_info(err_code));
        fclose(fp);
        return;
    }
    printf( "hci_tts_session_start success\n" );

	string synth_config;
	if (cap_key.find("tts.cloud.synth") != string::npos)
	{
		//property ���� ˽���� �ƶ����� ���������������ο������ֲ�
		//none: ���б�ǽ��ᱻ��Ϊ�ı�������ȱʡֵ
		synth_config = "property=cn_xiaokun_common,tagmode=none";
	}

	if (cap_key.find("tts.local.synth.sing") != string::npos)
	{
		synth_config = "tagmode=s3ml_sing";
	}

    //��ȡAccountInfo����
    AccountInfo *account_info = AccountInfo::GetInstance();
    if (!account_info->tts_speed().empty())
    {
        synth_config += ",speed=" + account_info->tts_speed();
    }
    if (!account_info->tts_volume().empty())
    {
        synth_config += ",volume=" + account_info->tts_volume();
    }
    if (!account_info->tts_audio_format().empty())
    {
        synth_config += ",audioFormat=" + account_info->tts_audio_format();
    }
    printf("%s\n", synth_config.c_str());

    err_code = hci_tts_synth( session_id, (char*)txt_data.buff_, synth_config.c_str(), TtsSynthCallbackFunction, fp );
    fclose(fp);

    if( err_code != HCI_ERR_NONE )
    {
        printf("hci_tts_session_start return (%d:%s) \n",err_code,hci_get_error_info(err_code));
    }

    // ��ֹ TTS Session
    err_code = hci_tts_session_stop( session_id );
    if( err_code != HCI_ERR_NONE )
    {
        printf( "hci_tts_session_stop return %d\n", err_code );
        return;
    }
    printf( "hci_tts_session_stop success\n" );

    return;
}
