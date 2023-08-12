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

`timescale 1ns / 1ps
module counter_toggle(
    input           clk,
    input           rstb,
    input           ena,
    input [31:0]    i_cntMax,
    output reg      o_toggle
    );

    reg [31:0] cnt;
    always @(negedge rstb or posedge clk)begin
        if(!rstb)
            cnt <= 'b0;
        else if(!ena)
            cnt <= 'b0;
        else if(cnt == i_cntMax-1)
            cnt <= 'b0;
        else
            cnt <= cnt+1;
    end

    always@(negedge rstb or posedge clk)begin
        if(!rstb)
            o_toggle <= 0;
        else if(!ena)
            o_toggle <= 0;
        else if(cnt == i_cntMax-1)
            o_toggle <= ~o_toggle;
    end
endmodule
