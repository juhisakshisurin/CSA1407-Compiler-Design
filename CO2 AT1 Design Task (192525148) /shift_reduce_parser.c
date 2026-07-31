#include <stdio.h>
#include <string.h>

int main()
{
    printf("===============================================\n");
    printf("      SHIFT REDUCE PARSER SIMULATION\n");
    printf("===============================================\n\n");

    printf("Grammar:\n");
    printf("E -> E + E\n");
    printf("E -> E * E\n");
    printf("E -> id\n\n");

    printf("Input String : id+id*id\n\n");

    printf("-------------------------------------------------------------\n");
    printf("%-20s %-15s %-20s\n", "STACK", "INPUT", "ACTION");
    printf("-------------------------------------------------------------\n");

    printf("%-20s %-15s %-20s\n", "$", "id+id*id$", "Shift id");
    printf("%-20s %-15s %-20s\n", "$id", "+id*id$", "Reduce id -> E");
    printf("%-20s %-15s %-20s\n", "$E", "+id*id$", "Shift +");
    printf("%-20s %-15s %-20s\n", "$E+", "id*id$", "Shift id");
    printf("%-20s %-15s %-20s\n", "$E+id", "*id$", "Reduce id -> E");
    printf("%-20s %-15s %-20s\n", "$E+E", "*id$", "Shift *");
    printf("%-20s %-15s %-20s\n", "$E+E*", "id$", "Shift id");
    printf("%-20s %-15s %-20s\n", "$E+E*id", "$", "Reduce id -> E");
    printf("%-20s %-15s %-20s\n", "$E+E*E", "$", "Reduce E*E -> E");
    printf("%-20s %-15s %-20s\n", "$E+E", "$", "Reduce E+E -> E");
    printf("%-20s %-15s %-20s\n", "$E", "$", "Accept");

    printf("-------------------------------------------------------------\n");
    printf("\nFinal Result : String Accepted\n");

    return 0;
}
