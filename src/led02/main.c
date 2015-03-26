#include "stm32f4_discovery.h"

#define GREEN  LED3_PIN
#define ORANGE LED4_PIN
#define RED    LED5_PIN
#define BLUE   LED6_PIN
#define ALL_LEDS (GREEN | ORANGE | RED | BLUE) // all leds
#define PAUSE_LONG  4000000L
#define PAUSE_SHORT 1000000L

#define LEDS_GPIO_PORT (GPIOD)

static uint16_t leds[LEDn] = {GREEN, ORANGE, RED, BLUE};
GPIO_InitTypeDef GPIO_InitStructure;

void myDelay(){
    uint32_t ii;
    ii=0;
    //1,000,000回ループを回る
    while(ii<1000000){
        ii++;
    }
}

int main(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;

    //GPIO初期化################################
    //GPIO初期化のための構造体GPIO_InitStructureを作る
    GPIO_InitTypeDef GPIO_InitStructure;

    //PORTAの設定開始(INPUT)---------------------------------
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    //初期化用構造体にパラメータをセットしていくため、いったん初期値に戻す
    GPIO_StructInit(&GPIO_InitStructure);
    //設定するピンを指定する（スイッチのピン・アクティブハイ）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    //指定したピンを入力に指定する
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    //プルアップを使用しない
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    //GPIOのスピードを100MHz（最高速）にセットする
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

    //PORTA設定入力終了。これでGPIOAを設定する
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //PORTAの設定終了----------------------------------------

    //PORTDの設定開始(OUTPUT)--------------------------------
    //PORTDにクロックの供給を開始
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    //初期化用構造体にパラメータをセットしていくため、いったん初期値に戻す
    GPIO_StructInit(&GPIO_InitStructure);
    //設定するピンを指定する（４つのLED）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15;
    //指定したピンを出力に指定する
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    //出力ポートのタイプをプッシュプルに指定する
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    //プルアップを使用しない
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    //GPIOのスピードを100MHz（最高速）にセットする
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

    //PORTD設定入力終了。これでGPIODを設定する
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //PORTDの初期値設定（LEDをすべて消灯）
    GPIO_ResetBits(GPIOD,GPIO_Pin_12);
    GPIO_ResetBits(GPIOD,GPIO_Pin_13);
    GPIO_ResetBits(GPIOD,GPIO_Pin_14);
    GPIO_ResetBits(GPIOD,GPIO_Pin_15);
    //PORTDの設定終了----------------------------------------

    //ここからプログラム本体################################
    //ボタンを押している間LEDを点滅する無限ループ
    while (1)
    {
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)){
            //ボタンが押されて１になっていたら以下を実行
            //GPIO_SetBits(GPIOD,GPIO_Pin_13); //LED点灯
            //GPIO_SetBits(GPIOD,GPIO_Pin_14);
            GPIO_SetBits(GPIOD,GPIO_Pin_12);
            myDelay();
            //GPIO_ResetBits(GPIOD,GPIO_Pin_13); //LED消灯
            //GPIO_ResetBits(GPIOD,GPIO_Pin_14); //LED消灯
            GPIO_ResetBits(GPIOD,GPIO_Pin_12); //LED消灯
            myDelay();
        }
    }
    return 0; // never returns actually
}


