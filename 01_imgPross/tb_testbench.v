//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/04/2023 01:39:36 PM
// Design Name: 
// Module Name: counter_toggle
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
`define FTIME 7000
`timescale 1ns / 1ps
module tb_testbench();

    reg CLK, RSTB;
    reg [3:0] SWT;
    wire [3:0] LED;

    imgConv u1(
        .clk(CLK),
        .rstb(RSTB),
        .swt(SWT),
        .led(LED)
    );

    always@(*)begin
        #4
        CLK <= !CLK;
    end

    initial begin
        CLK <= 0;
        SWT <= 0;
        RSTB <= 0;
        #`FTIME;
        $finish;
    end

    initial begin
        #100
        RSTB <= 1;
        #10
        SWT <= 4'b0001;
        #1000
        SWT <= 4'b0010;
        #1000
        SWT <= 4'b0100;
        #1000
        SWT <= 4'b1000;
        #1000 
        SWT <= 4'b1001;
        #1000
        SWT <= 4'b0110;
    end
endmodule