
# Tarefa: Roteiro de FreeRTOS #1 - EmbarcaTech 2025

Autor: **Guilherme Achilles de Oliveira e Aguiar**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, 10/06 de 2025

---

### Divisão da tarefa

A tarefa foi dividida nas pastas:

* **Driver**: controle e inicialização dos periféricos usados.
* **src**: contém o executável do projeto (main).
* **Include**: contém os headers de todos os arquivos `.c` e a configuração do FreeRTOS.

### Inserindo o FreeRTOS

Para integrar o microkernel FreeRTOS ao projeto, foi feito o clone do repositório oficial do GitHub e adicionada uma cópia na pasta do projeto.

Em seguida, no `CMakeLists.txt`, inclua:

```cmake
set(FREERTOS_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS)
message(STATUS "FreeRTOS Kernel located in ${FREERTOS_PATH}")
include(${FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)
target_link_libraries(Atividade_1_free_rtos
    FreeRTOS-Kernel-Heap4)
```

### Criando as Tasks

1. **Task de troca de cores** (prioridade 2)

   * Alterna LEDs a cada 500 ms nas cores verde, azul e vermelho.
   * Usa `vTaskDelay(pdMS_TO_TICKS(500));` para controlar o tempo.

   ```c
   void changeColor_task(void *params) {
       while (1) {
           led_on(11); // Verde
           vTaskDelay(pdMS_TO_TICKS(500));
           led_off(11);

           led_on(12); // Azul
           vTaskDelay(pdMS_TO_TICKS(500));
           led_off(12);

           led_on(13); // Vermelho
           vTaskDelay(pdMS_TO_TICKS(500));
           led_off(13);
       }
   }
   ```

2. **Task do buzzer** (prioridade 2)

   * Aciona o buzzer a cada 1 segundo: 500 ms ligado e 500 ms desligado, gerando 1 Hz.

   ```c
   void playBuzzer_task(void *params) {
       while (1) {
           buzzer_on();
           vTaskDelay(pdMS_TO_TICKS(500));
           buzzer_off();
           vTaskDelay(pdMS_TO_TICKS(500));
       }
   }
   ```

3. **Task de leitura de botões** (prioridade 1)

   * Monitora botões para suspender e retomar a task de troca de cores.
   * Usa `vTaskSuspend` e `vTaskResume` com o handle da task, o primeiro para interromper a task e o segundo para retomar.

   ```c
   void buttonInterrupt_task(void *params) {
       while (1) {
           if (button_pressed()) {
               vTaskSuspend(handle_changeColor);
           } else {
               vTaskResume(handle_changeColor);
           }
           vTaskDelay(pdMS_TO_TICKS(50)); // Debounce
       }
   }
   ```

4. **Inicialização das tasks e scheduler**

   ```c
   // Criação das tasks
   xTaskCreate(changeColor_task,   "Blink",  256, NULL, 2, &handle_changeColor);
   xTaskCreate(playBuzzer_task,    "Play",   256, NULL, 2, &handle_playBuzzer);
   xTaskCreate(buttonInterrupt_task, "Buttons",256, NULL, 1, NULL);

   // Inicia o escalonador do FreeRTOS
   vTaskStartScheduler();

   ```

### Reflexões

- Se todas as tarefas tiverem a mesma prioridade, o kernel do FreeRtos vai fazer um round-roubin entre as tasks. Ela vão ainda ser feitas de forma "paralela", quando uma task for pausada, parte da outra vai começar a ser feita, até todas serem finalizadas.

- Quem ocupa mais tempo de CPU é a verificação dos botões. Considerando todas as funções das tasks como simples, pois é verificar um estado de uma gpio ou colocar um estado nela, igualando esses termos, temos que a task do botão é executada mais vezes, ocupando uma porcentagem maior da cpu em todo periodo de tempo em que o microcontrolador esta ligado.

-  A consequência disto, é que se você tem uma task, mais importante, que dependa da entrada do usuario, ela tem chance de não ser executada no momento em que deveria ser executada, pois sua prioridade é a mesma ou inferior a das outras tarefas. 


### Video da tarefa em funcionamento 
https://www.youtube.com/shorts/y4WeQf1E2f0
---

## 📜 Licença
GNU GPL-3.0.
