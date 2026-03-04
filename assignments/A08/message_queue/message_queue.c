#include "message_queue.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <stdlib.h>
#include <stdio.h>

/*
 * The commands supported by the server
 */
typedef enum _Command {
    CmdExit      = 0x00,     // Stops the server

    CmdAdd,                  // Adds the two message parameters
    CmdSubtract              // Subtracts the two message parameters
} Command;

/*
 * The message format to be sent to the server.
 */
typedef struct _Message {
    /*
     * One of the command constants.
     */
    Command command;
    /*
     * Used as operand 1 (if required)
     */
    int parameter1;
    /*
     * Used as operand 2 (if required)
     */
    int parameter2;
} Message;

#define QUEUE_NAME "/simple_calculator"

#define FORMAT_STRING_ADD      "%d + %d = %d\n"
#define FORMAT_STRING_SUBTRACT "%d - %d = %d\n"

mqd_t startClient(void)
{
    // TODO: Open the message queue previously created by the server
    mqd_t client = mq_open(QUEUE_NAME, O_WRONLY);

    return client;
}

int sendExitTask(mqd_t client)
{
    (void)client;

    // TODO: Send the exit command to the server.
    Message msg;
    msg.command = CmdExit;
    return mq_send(client, (const char *)&msg, sizeof(Message), 0);
}

int sendAddTask(mqd_t client, int operand1, int operand2)
{
    (void)client;
    (void)operand1;
    (void)operand2;

    // TODO: Send the add command with the operands
    Message msg;
    msg.command = CmdAdd;
    msg.parameter1 = operand1;
    msg.parameter2 = operand2;
    return mq_send(client, (const char *)&msg, sizeof(Message), 0);
}

int sendSubtractTask(mqd_t client, int operand1, int operand2)
{
    (void)client;
    (void)operand1;
    (void)operand2;

    // TODO: Send the sub command with the operands
    Message msg;
    msg.command = CmdSubtract;
    msg.parameter1 = operand1;
    msg.parameter2 = operand2;

    // Senden der Subtraktions-Anforderung
    return mq_send(client, (const char *)&msg, sizeof(Message), 0);
}

int stopClient(mqd_t client)
{
    (void)client;

    // TODO: Clean up anything on the client-side
    return mq_close(client);
}

int runServer(void)
{
    // TODO: Implement the server
    struct mq_attr attr;
    attr.mq_flags = 0;               // Flags (werden bei mq_open ignoriert)
    attr.mq_maxmsg = 10;             // Anforderung: "space for 10 messages"
    attr.mq_msgsize = sizeof(Message); // Anforderung: "takes Message structures"
    attr.mq_curmsgs = 0;             // Aktuelle Nachrichten (wird ignoriert)

    mqd_t message_queue = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY | O_EXCL, 0644, &attr);
    if (message_queue == (mqd_t)-1) {
        return -1;
    }
    int returnValue = 0;
    Message msg;
    while (1) {
        // "Receive the message ... with the highest priority" 
        // Der Puffer muss mindestens mq_msgsize groß sein.
        ssize_t bytes_read = mq_receive(message_queue, (char *)&msg, sizeof(Message), NULL);

        if (bytes_read == -1) {
            returnValue = -1; // Fehler beim Empfangen
            break;
        }

        // Verarbeitung der Befehle
        if (msg.command == CmdExit) {
            // "CmdExit Exits the server"
            returnValue = 0;
            break;
        } 
        else if (msg.command == CmdAdd) {
            // "Adds the two parameters ... prints the result"
            int result = msg.parameter1 + msg.parameter2;
            printf(FORMAT_STRING_ADD, msg.parameter1, msg.parameter2, result);
        } 
        else if (msg.command == CmdSubtract) {
            // "Subtracts the second ... from the first ... prints the result"
            int result = msg.parameter1 - msg.parameter2;
            printf(FORMAT_STRING_SUBTRACT, msg.parameter1, msg.parameter2, result);
        } 
        else {
            // "Exits ... on reception of an unknown command"
            returnValue = -1; // Unbekannter Befehl wird als Fehler gewertet
            break;
        }
    }

    // 4. Aufräumen (Cleanup)
    // "Closes the message queue on exit and unlinks it." [cite: 188, 225]
    mq_close(message_queue);
    mq_unlink(QUEUE_NAME);

    return returnValue;
}